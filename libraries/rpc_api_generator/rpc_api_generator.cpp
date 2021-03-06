#include <contento/rpc_api_generator/rpc_api_generator.hpp>
#include <contento/rpc_api_generator/rpc_api_def.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

namespace contento {

   vector<type_def> common_type_defs() {
      vector<type_def> types;

      types.push_back( type_def{"account_name", "namex"} );
      types.push_back( type_def{"action_name", "name"} );
      types.push_back( type_def{"transaction_id_type", "checksum160"} );
      types.push_back( type_def{"block_id_type", "checksum160"} );
      types.push_back( type_def{"weight_type", "uint16"} );

      types.push_back( type_def{"account_name_type", "namex"} );
      types.push_back( type_def{"share_type", "int64"} );
      types.push_back( type_def{"id_type", "int64"} );
      types.push_back( type_def{"digest_type", "checksum256"} );

      types.push_back( type_def{"checksum_type", "checksum160"} );


      return types;
   }


void rpc_api_generator::set_target_contract(const rpc_api_macro_def_result& actions) {
  target_actions  = actions;
}

void rpc_api_generator::enable_optimizaton(rpc_api_generator::optimization o) {
  optimizations |= o;
}

bool rpc_api_generator::is_opt_enabled(rpc_api_generator::optimization o) {
  return (optimizations & o) != 0;
}

void rpc_api_generator::set_output(abi_def& output) {
  this->output = &output;
}

void rpc_api_generator::set_verbose(bool verbose) {
  this->verbose = verbose;
}


void rpc_api_generator::set_abi_context(const string& abi_context) {
  this->abi_context = abi_context;
}

void rpc_api_generator::set_compiler_instance(CompilerInstance& compiler_instance) {
  this->compiler_instance = &compiler_instance;
}

void rpc_api_generator::handle_tagdecl_definition(TagDecl* tag_decl) {
  ast_context = &tag_decl->getASTContext();
  auto decl_location = tag_decl->getLocation().printToString(ast_context->getSourceManager());
  try {
  handle_decl(tag_decl);
} FC_CAPTURE_AND_RETHROW((decl_location)) }

string rpc_api_generator::remove_namespace(const string& full_name) {
   int i = full_name.size();
   int on_spec = 0;
   int colons = 0;
   while( --i >= 0 ) {
      if( full_name[i] == '>' ) {
         ++on_spec; colons=0;
      } else if( full_name[i] == '<' ) {
         --on_spec; colons=0;
      } else if( full_name[i] == ':' && !on_spec) {
         if (++colons == 2)
            return full_name.substr(i+2);
      } else {
         colons = 0;
      }
   }
   return full_name;
}

bool rpc_api_generator::is_builtin_type(const string& type_name) {
  rpc_api_serializer serializer;
  auto rtype = resolve_type(type_name);
  return serializer.is_builtin_type(translate_type(rtype));
}

string rpc_api_generator::translate_type(const string& type_name) {
  string built_in_type = type_name;

  if (type_name == "unsigned __int128" || type_name == "uint128_t") built_in_type = "uint128";
  else if (type_name == "__int128"          || type_name == "int128_t")  built_in_type = "int128";

  else if (type_name == "unsigned long long" || type_name == "uint64_t") built_in_type = "uint64";
  else if (type_name == "unsigned long"      || type_name == "uint32_t") built_in_type = "uint32";
  else if (type_name == "unsigned short"     || type_name == "uint16_t") built_in_type = "uint16";
  else if (type_name == "unsigned char"      || type_name == "uint8_t")  built_in_type = "uint8";

  else if (type_name == "long long"          || type_name == "int64_t")  built_in_type = "int64";
  else if (type_name == "long"               || type_name == "int32_t")  built_in_type = "int32";
  else if (type_name == "int"                )  built_in_type = "int32";
  else if (type_name == "short"              || type_name == "int16_t")  built_in_type = "int16";
  else if (type_name == "char"               || type_name == "int8_t")   built_in_type = "int8";
  else if (type_name == "double")   built_in_type = "float64";
  else if (type_name == "fixed_string_16")   built_in_type = "string16";

  else if (boost::starts_with(type_name, "oid<"))   built_in_type = "id_type";
  else {
     static auto types = common_type_defs();
     auto itr = std::find_if( types.begin(), types.end(),
                              [&type_name]( const contento::rpc_api::type_def& t ) { return t.new_type_name == type_name; } );
     if( itr != types.end()) {
        built_in_type = itr->type;
     }
  }

  return built_in_type;
}

bool rpc_api_generator::inspect_type_methods_for_actions(const Decl* decl) { try {

  const auto* rec_decl = dyn_cast<CXXRecordDecl>(decl);
  if(rec_decl == nullptr) return false;

  const auto* type = rec_decl->getTypeForDecl();
  ABI_ASSERT(type != nullptr);

  bool at_least_one_action = false;
  class_def abi_class;
  abi_class.name = rec_decl->getNameAsString();

   vector<string>& filter_classes = target_actions.filter_classes;
   if ( std::find( filter_classes.begin(), filter_classes.end(), abi_class.name ) != filter_classes.end() )
      return false;

  if ( target_actions.functions_map.find( abi_class.name ) == target_actions.functions_map.end() )
     return false;

  vector<string>& defined_function = target_actions.functions_map[abi_class.name];

  auto export_method = [&](const CXXMethodDecl* method) {
    auto method_name = method->getNameAsString();
     string filter_function = abi_class.name + "/" + method_name;

     vector<string>& filter_funs = target_actions.filter_functions;
     if ( std::find( filter_funs.begin(), filter_funs.end(), filter_function ) != filter_funs.end() )
        return;

     if ( std::find(defined_function.begin(),defined_function.end(),method_name ) == defined_function.end() )
        return;

    // Try to get "action" annotation from method comment
    bool raw_comment_is_action = false;
    const RawComment* raw_comment = ast_context->getRawCommentForDeclNoCache(method);
    if(raw_comment != nullptr) {
      SourceManager& source_manager = ast_context->getSourceManager();
      string raw_text = raw_comment->getRawText(source_manager);
      regex r(R"(@abi (action)((?: [a-z0-9]+)*))");
      smatch smatch;
      regex_search(raw_text, smatch, r);
      raw_comment_is_action = smatch.size() == 3;
    }

    // Check if current method is listed the contento_ABI macro
     bool is_action_from_macro = false;

     string class_name = string(rec_decl->getName().str());
     if ( target_actions.functions_map.find(class_name) != target_actions.functions_map.end() ){
        const vector<string>& func_lists = target_actions.functions_map[class_name];

        is_action_from_macro = std::find(func_lists.begin(), func_lists.end(), method_name) != func_lists.end();
     }
    
    if(!raw_comment_is_action && !is_action_from_macro) {
      return;
    }

    ABI_ASSERT(find_struct(method_name) == nullptr, "action already exists ${method_name}", ("method_name",method_name));

    function_def func_struct;
    for(const auto* p : method->parameters() ) {
      clang::QualType qt = p->getOriginalType().getNonReferenceType();
      qt.setLocalFastQualifiers(0);

      string field_name = p->getNameAsString();
      string field_type_name = add_type(qt, 0);

      field_def struct_field{field_name, field_type_name};
      check_container_support(field_type_name);
      type_size[string(struct_field.type)] = is_vector(struct_field.type) ? 0 : ast_context->getTypeSize(qt);
      func_struct.fields.push_back(struct_field);
    }

    clang::QualType qt = method->getReturnType().getNonReferenceType();
    qt.setLocalFastQualifiers(0);
    string ret_type_name = add_type(qt, 0);

    check_container_support(ret_type_name);

    func_struct.ret = { ret_type_name };
    func_struct.name = method_name;

    //output->structs.push_back(abi_struct);

    full_types[method_name] = method_name;

    abi_class.functions.push_back(func_struct);
    at_least_one_action = true;
  };

  const auto export_methods = [&export_method](const CXXRecordDecl* rec_decl) {


    auto export_methods_impl = [&export_method](const CXXRecordDecl* rec_decl, auto& ref) -> void {


      auto tmp = rec_decl->bases();
      auto rec_name = rec_decl->getName().str();

      rec_decl->forallBases([&ref](const CXXRecordDecl* base) -> bool {
        ref(base, ref);
        return true;
      });

      for(const auto* method : rec_decl->methods()) {
        export_method(method);
      }

    };

    export_methods_impl(rec_decl, export_methods_impl);
  };

  export_methods(rec_decl);

   output->classes.push_back(abi_class);
  return at_least_one_action;

} FC_CAPTURE_AND_RETHROW() }

void rpc_api_generator::handle_decl(const Decl* decl) { try {

  ABI_ASSERT(decl != nullptr);
  ABI_ASSERT(output != nullptr);
  ABI_ASSERT(ast_context != nullptr);

  // Only process declarations that has the `abi_context` folder as parent.
  SourceManager& source_manager = ast_context->getSourceManager();
  auto file_name = source_manager.getFilename(decl->getLocStart());
  if ( !abi_context.empty() && !file_name.startswith(abi_context) ) {
    return;
  }

  // Check if the current declaration has actions (contento_ABI, or explicit)
  bool type_has_actions = inspect_type_methods_for_actions(decl);
  if( type_has_actions ) return;


} FC_CAPTURE_AND_RETHROW() }

bool rpc_api_generator::is_64bit(const string& type) {
  return type_size[type] == 64;
}

bool rpc_api_generator::is_128bit(const string& type) {
  return type_size[type] == 128;
}

bool rpc_api_generator::is_string(const string& type) {
  return type == "String" || type == "string";
}

void rpc_api_generator::get_all_fields(const struct_def& s, vector<field_def>& fields) {
  rpc_api_serializer abis(*output);

  for(const auto& field : s.fields) {
    fields.push_back(field);
  }

  if(s.base.size()) {
    const auto* base = find_struct(s.base);
    ABI_ASSERT(base, "Unable to find base type ${type}",("type",s.base));
    get_all_fields(*base, fields);
  }
}

bool rpc_api_generator::is_i64_index(const vector<field_def>& fields) {
  return fields.size() >= 1 && is_64bit(fields[0].type);
}

//void rpc_api_generator::guess_index_type(table_def& table, const struct_def s) {
//  vector<field_def> fields;
//  get_all_fields(s, fields);
//  if( is_i64_index(fields) ) {
//    table.index_type = "i64";
//  } else {
//    ABI_ASSERT(false, "Unable to guess index type");
//  }
//}

//void rpc_api_generator::guess_key_names(table_def& table, const struct_def s) {
//
//  vector<field_def> fields;
//  get_all_fields(s, fields);
//
// if( table.index_type == "i64") {
//
//    table.key_names.clear();
//    table.key_types.clear();
//
//    unsigned int key_size = 0;
//    bool valid_key = false;
//    for(auto& f : fields) {
//      table.key_names.emplace_back(f.name);
//      table.key_types.emplace_back(f.type);
//      key_size += type_size[f.type]/8;
//
//      if(table.index_type == "i64" && key_size >= sizeof(uint64_t)) {
//        valid_key = true;
//        break;
//      }
//    }
//
//    ABI_ASSERT(valid_key, "Unable to guess key names");
//  } else {
//    ABI_ASSERT(false, "Unable to guess key names");
//  }
//}
//
//const table_def* rpc_api_generator::find_table(const table_name& name) {
//  for( const auto& ta : output->tables ) {
//    if(ta.name == name) {
//      return &ta;
//    }
//  }
//  return nullptr;
//}

const type_def* rpc_api_generator::find_type(const type_name& new_type_name) {
  for( const auto& td : output->types ) {
    if(td.new_type_name == new_type_name) {
      return &td;
    }
  }
  return nullptr;
}

//const action_def* rpc_api_generator::find_action(const action_name& name) {
//  for( const auto& ac : output->actions ) {
//    if(ac.name == name) {
//      return &ac;
//    }
//  }
//  return nullptr;
//}

const struct_def* rpc_api_generator::find_struct(const type_name& name) {
  auto rname = resolve_type(name);
  for( const auto& st : output->structs ) {
    if(st.name == rname) {
      return &st;
    }
  }
  return nullptr;
}

type_name rpc_api_generator::resolve_type(const type_name& type){
  const auto* td = find_type(type);
  if( td ) {
    for( auto i = output->types.size(); i > 0; --i ) { // avoid infinite recursion
      const type_name& t = td->type;
      td = find_type(t);
      if( td == nullptr ) return t;
    }
  }
  return type;
}

bool rpc_api_generator::is_one_filed_no_base(const string& type_name) {
  const auto* s = find_struct(type_name);
  return s && s->base.size() == 0 && s->fields.size() == 1;
}

string rpc_api_generator::decl_to_string(clang::Decl* d) {
    //ASTContext& ctx = d->getASTContext();
    const auto& sm = ast_context->getSourceManager();
    clang::SourceLocation b(d->getLocStart()), _e(d->getLocEnd());
    clang::SourceLocation e(clang::Lexer::getLocForEndOfToken(_e, 0, sm, compiler_instance->getLangOpts()));
    return string(sm.getCharacterData(b),
        sm.getCharacterData(e)-sm.getCharacterData(b));
}

bool rpc_api_generator::is_typedef(const clang::QualType& qt) {
  return isa<TypedefType>(qt.getTypePtr());
}

bool rpc_api_generator::is_elaborated(const clang::QualType& qt) {
  return isa<ElaboratedType>(qt.getTypePtr());
}

bool rpc_api_generator::is_vector(const clang::QualType& vqt) {

  QualType qt(vqt);

  if ( is_elaborated(qt) )
    qt = qt->getAs<clang::ElaboratedType>()->getNamedType();

  return isa<clang::TemplateSpecializationType>(qt.getTypePtr()) \
   && ( boost::starts_with( get_type_name(qt, false), "vector") || boost::starts_with( get_type_name(qt, false), "optional")
       || boost::starts_with( get_type_name(qt, true), "boost::container::flat_set")
       || boost::starts_with( get_type_name(qt, true), "std::set")
       || boost::starts_with( get_type_name(qt, false), "deque")
       );
}

bool rpc_api_generator::is_unions(const clang::QualType& vqt) {

   QualType qt(vqt);

   if ( is_elaborated(qt) )
      qt = qt->getAs<clang::ElaboratedType>()->getNamedType();

   return isa<clang::TemplateSpecializationType>(qt.getTypePtr()) &&  boost::starts_with( get_type_name(qt, true), "fc::static_variant");
}

bool rpc_api_generator::is_vector(const string& type_name) {
  return boost::ends_with(type_name, "[]");
}

bool rpc_api_generator::is_map(const clang::QualType& vqt){
   QualType qt(vqt);

   if ( is_elaborated(qt) )
      qt = qt->getAs<clang::ElaboratedType>()->getNamedType();

   return isa<clang::TemplateSpecializationType>(qt.getTypePtr()) \
   && ( boost::starts_with( get_type_name(qt, false), "map") || boost::starts_with( get_type_name(qt, false), "flat_map") || boost::starts_with( get_type_name(qt, true), "std::pair") );
}
bool rpc_api_generator::is_map(const string& type_name){
   return boost::starts_with(type_name, "{") && boost::ends_with(type_name, "}");
}


bool rpc_api_generator::is_struct_specialization(const clang::QualType& qt) {
  return is_struct(qt) && isa<clang::TemplateSpecializationType>(qt.getTypePtr());
}

bool rpc_api_generator::is_struct(const clang::QualType& sqt) {
  clang::QualType qt(sqt);
  const auto* type = qt.getTypePtr();
  return !is_vector(qt) && !is_map(qt) && (type->isStructureType() || type->isClassType());
}

clang::QualType rpc_api_generator::get_vector_element_type(const clang::QualType& qt) {
  const auto* tst = clang::dyn_cast<const clang::TemplateSpecializationType>(qt.getTypePtr());
  ABI_ASSERT(tst != nullptr);
  const clang::TemplateArgument& arg0 = tst->getArg(0);
  return arg0.getAsType();
}

QualType rpc_api_generator::get_map_key_element_type(const clang::QualType& qt){
   const auto* tst = clang::dyn_cast<const clang::TemplateSpecializationType>(qt.getTypePtr());
   ABI_ASSERT(tst != nullptr);
   const clang::TemplateArgument& arg0 = tst->getArg(0);
   return arg0.getAsType();
}
QualType rpc_api_generator::get_map_value_element_type(const clang::QualType& qt){
   const auto* tst = clang::dyn_cast<const clang::TemplateSpecializationType>(qt.getTypePtr());
   ABI_ASSERT(tst != nullptr);
   const clang::TemplateArgument& arg0 = tst->getArg(1);
   return arg0.getAsType();
}

string rpc_api_generator::get_vector_element_type(const string& type_name) {
  if( is_vector(type_name) )
    return type_name.substr(0, type_name.size()-2);
  return type_name;
}

string rpc_api_generator::get_map_element_type(const string& type_name, bool key) {
   if( is_map(type_name) ){
      string kv = type_name.substr(1, type_name.size()-2);
      std::vector<std::string> vecSegTag;
      boost::split(vecSegTag, kv,boost::is_any_of(","));
      return vecSegTag[key ? 0 : 1];
   }
   return type_name;
}

string rpc_api_generator::get_type_name(const clang::QualType& qt, bool with_namespace=false) {
  auto name = clang::TypeName::getFullyQualifiedName(qt, *ast_context);
  if(!with_namespace)
    name = remove_namespace(name);
  return name;
}

clang::QualType rpc_api_generator::add_typedef(const clang::QualType& tqt, size_t recursion_depth) {

  ABI_ASSERT( ++recursion_depth < max_recursion_depth, "recursive definition, max_recursion_depth" );

  clang::QualType qt(get_named_type_if_elaborated(tqt));

  const auto* td_decl = qt->getAs<clang::TypedefType>()->getDecl();
  auto underlying_type = td_decl->getUnderlyingType().getUnqualifiedType();

  auto new_type_name = td_decl->getName().str();
  auto underlying_type_name = get_type_name(underlying_type);

  if ( is_vector(underlying_type) ) {
    underlying_type_name = add_vector(underlying_type, recursion_depth);
  }

   if ( is_map(underlying_type) ) {
      underlying_type_name = add_map(underlying_type, recursion_depth);
   }

   if ( is_unions( underlying_type ) ){
      return underlying_type;
   }

  type_def abi_typedef;
  abi_typedef.new_type_name = new_type_name;
  abi_typedef.type = translate_type(underlying_type_name);
  const auto* td = find_type(abi_typedef.new_type_name);

  if(!td && (!is_struct_specialization(underlying_type) || abi_typedef.type == "id_type") ) {
    output->types.push_back(abi_typedef);
  } else {
    if(td) ABI_ASSERT(abi_typedef.type == td->type);
  }

  if( is_typedef(underlying_type) && !is_builtin_type(get_type_name(underlying_type)) )
    return add_typedef(underlying_type, recursion_depth);

  return underlying_type;
}

clang::CXXRecordDecl::base_class_range rpc_api_generator::get_struct_bases(const clang::QualType& sqt) {

  clang::QualType qt(sqt);
  if(is_typedef(qt)) {
    const auto* td_decl = qt->getAs<clang::TypedefType>()->getDecl();
    qt = td_decl->getUnderlyingType().getUnqualifiedType();
  }

  const auto* record_type = qt->getAs<clang::RecordType>();
  ABI_ASSERT(record_type != nullptr);
  auto cxxrecord_decl = clang::dyn_cast<CXXRecordDecl>(record_type->getDecl());
  ABI_ASSERT(cxxrecord_decl != nullptr);
  //record_type->getCanonicalTypeInternal().dump();
  ABI_ASSERT(cxxrecord_decl->hasDefinition(), "No definition for ${t}", ("t", qt.getAsString()));

  auto bases = cxxrecord_decl->bases();

  return bases;
}

const clang::RecordDecl::field_range rpc_api_generator::get_struct_fields(const clang::QualType& sqt) {
  clang::QualType qt(sqt);

  if(is_typedef(qt)) {
    const auto* td_decl = qt->getAs<clang::TypedefType>()->getDecl();
    qt = td_decl->getUnderlyingType().getUnqualifiedType();
  }

  const auto* record_type = qt->getAs<clang::RecordType>();
  ABI_ASSERT(record_type != nullptr);
  return record_type->getDecl()->fields();
}

string rpc_api_generator::add_unions(const clang::QualType& uqt, string full_name, size_t recursion_depth){

   string type_name = remove_namespace(full_name);

   if( find_struct(type_name) ) {
      return type_name;
   }

   clang::QualType qt(get_named_type_if_elaborated(uqt));
   const auto* tst = clang::dyn_cast<const clang::TemplateSpecializationType>(qt.getTypePtr());
   ABI_ASSERT(tst != nullptr);

   struct_def abi_struct;
   for ( int i = 0; i < tst->getNumArgs(); i++){
      auto arg = tst->getArg(i).getAsType();
      string uion_type = add_type(arg, recursion_depth);
      //output->operations.emplace_back(op_name);

      string field_name = (boost::format("u_%d") % i).str();
      abi_struct.fields.push_back( {field_name, uion_type}  );
   }

   abi_struct.name      = type_name;
   abi_struct.isunion   = true;

   output->structs.push_back(abi_struct);

   return type_name;
}

string rpc_api_generator::add_vector(const clang::QualType& vqt, size_t recursion_depth) {

  ABI_ASSERT( ++recursion_depth < max_recursion_depth, "recursive definition, max_recursion_depth" );

  clang::QualType qt(get_named_type_if_elaborated(vqt));

  auto vector_element_type = get_vector_element_type(qt);

   bool is_two_dimens = false;
   if ( is_vector(vector_element_type) ){
      vector_element_type = get_vector_element_type(vector_element_type);
      ABI_ASSERT(!is_vector(vector_element_type), "Only two-dimensional arrays are supported");
      is_two_dimens = true;
   }

  string result = add_type(vector_element_type, recursion_depth);

  auto vector_element_type_str = translate_type(result);
  vector_element_type_str += "[]";

   if (is_two_dimens)
      vector_element_type_str += "[]";

  return vector_element_type_str;
}

string rpc_api_generator::add_operation(const clang::QualType& sqt, size_t recursion_depth){
   ABI_ASSERT( ++recursion_depth < max_recursion_depth, "recursive definition, max_recursion_depth" );

   clang::QualType tqt(get_named_type_if_elaborated(sqt));

   // already add ops
   if ( output->operations.size() > 0 ){
      return string("operation");
   }

   const auto* td_decl = tqt->getAs<clang::TypedefType>()->getDecl();
   auto underlying_type = td_decl->getUnderlyingType().getUnqualifiedType();

   clang::QualType qt(get_named_type_if_elaborated(underlying_type));
   std::cout <<  get_type_name(qt, false) << std::endl;

   const auto* tst = clang::dyn_cast<const clang::TemplateSpecializationType>(qt.getTypePtr());
   ABI_ASSERT(tst != nullptr);
   for ( int i = 0; i < tst->getNumArgs(); i++){
      auto arg = tst->getArg(i).getAsType();
      string op_name = add_type(arg, recursion_depth);
      output->operations.emplace_back(op_name);
   }
   return string("operation");
}

string rpc_api_generator::add_map(const clang::QualType& vqt, size_t recursion_depth){
   ABI_ASSERT( ++recursion_depth < max_recursion_depth, "recursive definition, max_recursion_depth" );

   clang::QualType qt(get_named_type_if_elaborated(vqt));

   auto key_element_type = get_map_key_element_type(qt);
   ABI_ASSERT(!is_map(key_element_type), "nested map did not supported");
   string key_desc = add_type(key_element_type, recursion_depth);

   auto value_element_type = get_map_value_element_type(qt);
   ABI_ASSERT(!is_map(value_element_type), "nested map did not supported");
   string value_desc = add_type(value_element_type, recursion_depth);

   auto map_key_element_type_str = translate_type(key_desc);
   auto map_value_element_type_str = translate_type(value_desc);

   string result = "{";
   result += map_key_element_type_str + "," + map_value_element_type_str + "}";
   return result;
}

string rpc_api_generator::add_type(const clang::QualType& tqt, size_t recursion_depth) {

  ABI_ASSERT( ++recursion_depth < max_recursion_depth, "recursive definition, max_recursion_depth" );

  clang::QualType qt(get_named_type_if_elaborated(tqt));

  string full_type_name = translate_type(get_type_name(qt, true));
  string type_name      = translate_type(get_type_name(qt));
  bool   is_type_def    = false;

  if( is_builtin_type(type_name) ) {
    return type_name;
  }

  if( is_typedef(qt) ) {
    qt = add_typedef(qt, recursion_depth);
    if( is_builtin_type(translate_type(get_type_name(qt))) ) {
      return type_name;
    }
    is_type_def = true;
  }

   if ( is_unions(qt) ){
      ABI_ASSERT(is_type_def, "unions must has typedef name");
      auto unions_type_name = add_unions(qt, full_type_name, recursion_depth);
      return is_type_def ? type_name : unions_type_name;
   }

  if( is_vector(qt) ) {
    auto vector_type_name = add_vector(qt, recursion_depth);
    return is_type_def ? type_name : vector_type_name;
  }

   if ( is_map(qt) ){
      auto map_type_name = add_map(qt, recursion_depth);
      return is_type_def ? type_name : map_type_name;
   }

  if( is_struct(qt) ) {
    return add_struct(qt, full_type_name, recursion_depth);
  }

   if ( qt.getTypePtr()->isEnumeralType() ){
      return "int64";
   }

  ABI_ASSERT(false, "types can only be: vector, struct, class or a built-in type. (${type}) ", ("type",get_type_name(qt)));
  return type_name;
}

clang::QualType rpc_api_generator::get_named_type_if_elaborated(const clang::QualType& qt) {
  if( is_elaborated(qt) ) {
    return qt->getAs<clang::ElaboratedType>()->getNamedType();
  }
  return qt;
}

bool rpc_api_generator::check_container_support(string type_name, size_t recursion_depth ){

   ABI_ASSERT(recursion_depth <= 2, "recursion_depth must less 3");

   if ( is_map(type_name) ){
      string key_type = get_map_element_type(type_name, true);
      check_container_support(key_type, recursion_depth + 1 );
      string value_type = get_map_element_type(type_name, false);
      check_container_support(value_type, recursion_depth + 1 );

   } else if ( is_vector(type_name) ){
      string vec_type = get_vector_element_type(type_name);
      check_container_support(vec_type, recursion_depth + 1 );
   }
   else {
      ABI_ASSERT(is_builtin_type(get_vector_element_type(type_name))
                 || find_struct(get_vector_element_type(type_name))
                 || find_type(get_vector_element_type(type_name))
                 , "Unknown type ${type} [${abi}]",("type",type_name)("abi",*output));
   }

   return true;
}


string rpc_api_generator::add_struct(const clang::QualType& sqt, string full_name, size_t recursion_depth) {

  ABI_ASSERT( ++recursion_depth < max_recursion_depth, "recursive definition, max_recursion_depth" );

  clang::QualType qt(get_named_type_if_elaborated(sqt));

   std::cout << "start add struct: " << full_name << std::endl;

  if( full_name.empty() ) {
    full_name = get_type_name(qt, true);
  }

  string name = remove_namespace(full_name);

  ABI_ASSERT(is_struct(qt), "Only struct and class are supported. ${full_name}",("full_name",full_name));

  if( find_struct(name) ) {
    auto itr = full_types.find(resolve_type(name));
    if(itr != full_types.end()) {
      ABI_ASSERT(itr->second == full_name, "Unable to add type '${full_name}' because '${conflict}' is already in.\n${t}", ("full_name",full_name)("conflict",itr->second)("t",output->types));
    }
    return name;
  }

   rpc_api_macro_def_structs macro_def;
   if ( target_actions.structs_map.find(name) == target_actions.structs_map.end() ){
      auto td = find_type(translate_type(name));
      if ( td != nullptr ){
         if ( target_actions.structs_map.find(td->type) == target_actions.structs_map.end() )
            ABI_ASSERT(0, "no FC_REFLECT define found");
         else{
            macro_def = target_actions.structs_map[td->type];
         }
      } else {
         ABI_ASSERT(0, "no FC_REFLECT define found");
      }
   } else {
      macro_def = target_actions.structs_map[name];
   }

  auto bases = get_struct_bases(qt);
  auto bitr = bases.begin();
  int total_bases = 0;

  string base_name;
  while( bitr != bases.end() ) {
    auto base_qt = bitr->getType();
    string base_name_check = get_type_name(base_qt, false);

    const auto* record_type = base_qt->getAs<clang::RecordType>();
    if( record_type && is_struct(base_qt) && !record_type->getDecl()->field_empty() ) {
      ABI_ASSERT(total_bases == 0, "Multiple inheritance not supported - ${type}", ("type",full_name));

      ABI_ASSERT( target_actions.structs_map[name].base_struct == base_name_check, "base declare not equal FC_RELECT" );

      base_name = add_type(base_qt, recursion_depth);
      ++total_bases;
    }
    ++bitr;
  }

  struct_def abi_struct;
  for (const clang::FieldDecl* field : get_struct_fields(qt) ) {
    clang::QualType qt = field->getType();

    string field_name = field->getNameAsString();

    string field_type_name = add_type(qt, recursion_depth);

    field_def struct_field{field_name, field_type_name};

    check_container_support(struct_field.type);

    type_size[string(struct_field.type)] = is_vector(struct_field.type) ? 0 : ast_context->getTypeSize(qt);

     if ( std::find( macro_def.members.begin(),macro_def.members.end(),field_name) != macro_def.members.end() ){
        abi_struct.fields.push_back(struct_field);
     } else {
        std::cout << "warning !!! no serial data: " << name << "::" << field_name << std::endl;
     }
  }

   map<string, int> sort_value;
   int n = 0;
   for( auto value : macro_def.members)
   {
      sort_value[value] = n++;
   }
   std::sort( abi_struct.fields.begin(), abi_struct.fields.end(), [&](const field_def& a, const field_def& b){
      return sort_value[a.name] < sort_value[b.name];
   });

  abi_struct.name = resolve_type(name);
  abi_struct.base = base_name;
  abi_struct.isunion = false;

  output->structs.push_back(abi_struct);

  full_types[name] = full_name;
  return name;
}

}
