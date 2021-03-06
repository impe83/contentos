## 帐号系统

帐号名是Contentos区块链帐号的唯一标识。有效的帐号名包含3～12个字符，每个字符可以是任意的小写英文字母、阿拉伯数字或句点。长度和字符集的限制条件，几乎不会增加用户选取合适名称的难度，但Contentos系统却可以在工程上大幅降低存储和提高名称查找匹配效率。

如果未来不得不打破帐号名的限制条件，Contentos可以通过部署Name service智能合约，建立新的命名体系，自动实现新旧帐号名的映射和解析工作。

### 权限和授权

Contentos帐号有3个内建的权限等级：Owner，Active，Posting。

- Owner权限：对帐号的绝对控制权，可以进行所有操作。
- Active权限：可以进行除修改帐号信息之外的所有操作。
- Posting权限：只可以进行社交操作，如发表内容或投票，不可以进行转账、买卖等影响帐号资产的操作。

内建权限各自对应一对公私钥。这3对公私钥在帐号创建时产生。用户使用任何一把私钥都可以成功登录，拥有对应的权限等级。例如，使用Posting私钥登录后，只能发表社交内容，无法转账和更改帐号信息。根据PoLP（权限最小化原则），用户使用合适权限的私钥登录，将极大降低帐号的安全风险。在绝大多数使用场景下，都不应该使用Owner私钥登录。

Contentos使用数字签名进行权限鉴定。用户发布一个transaction前，必须用自己的登录私钥对其签名。witness节点在收到transaction后，会首先验证数字签名是否合法，然后检查签名钥匙是否具备执行这个transaction的权限等级。如果检查不通过，transaction将被拒绝执行。

有时，用户会有把自己的权限和一个或多个其他帐号分享——即授权的需求。例如，一个组织O的官方blog有多个维护人员，每人都可以以O的名义发布内容。要实现这个群组blog功能，帐号O需要把它的posting权限授权给一组维护帐号。某个维护人员M发布一篇文章，声明作者是O，并用自己的（M的）私钥签名。Contentos将会检查签名钥匙是否具备O的posting权限，由于它已经授权给M，所以M的签名可以被接受。通过授权的方式，M在不知道O的私钥的情况下，能够以O的身份发布内容。

Contentos帐号权限的授权是始终存在的，默认情况下，Owner/Active/Posting权限分别授权给了对应的帐号公钥，即：只有用户自己拥有这些权限。对于任何一种权限等级，用户都可以更改授权信息，指定一个或多个授权对象。授权对象有2种：

- 其他帐号的公钥
- 其他帐号的用户名和权限

第2种情况有些复杂，但非常灵活。例如，user_a把自己的active权限授权给user_b@active，user_b又把自己的active权限授权给user_c@active。这样就形成了一条授权链。使用active私钥登录的user_c拥有user_a的active权限，虽然user_a没有直接授权给他。Contentos支持授权链的鉴定，但出于性能考虑限制了授权链的最大长度。幸运的是，大多数使用场景不会用到或者只需要很短的授权链。

Contentos还支持对授权对象分配权重，用于更加复杂的授权需求。比如，admin的owner权限授权给3个帐号user_a, user_b, user_c，他们的权重都是0.5，即每个人都只有“一半”权限，需要2个人的共同签名才能使用admin的owner权限。单个授权用户的私钥泄漏，并不会影响admin帐号的安全。这种多用户签名机制，能够大幅降低授权引入的安全风险。

### 并行权限鉴定

Contentos的帐号授权管理，和基于数字签名的权限鉴定机制，是与上层应用逻辑解耦的，并且是个“只读”过程。即使有些transaction会更改授权信息，改动在block生成之后才能生效。因此，所有transaction的权限鉴定可以并行进行，不必依赖复杂的应用逻辑。而且，p2p节点可以在刚刚接收到transaction时就开始鉴权操作，这些transaction被正式打包到block后需要执行时，不必重新鉴权。

权限鉴定是一个计算密集的过程，需要较多的运算时间。并行化的权限鉴定能够大幅提高Contentos整体的运行效率。

通过replay blocks重新生成区块链状态时，是可以省略权限鉴定的。因为一个合法block包含的所有transaction，在进入block时已经做过权限鉴定。这也可以显著提升replay的速度。

### 帐号恢复

用户的Owner私钥被盗并被修改时，可以通过Contentos的帐号恢复功能重新找回帐号。用户需要提供最近30天内有效的任何一个Owner私钥，由指定的恢复辅助帐号批准并发起帐号恢复申请，来重置用户帐号的Owner key。所有帐号都有自己的恢复辅助帐号，默认情况下，恢复辅助帐号是用户帐号的创建者。用户可以修改自己的恢复辅助帐号，一般设置成自己信任的好友帐号。

恢复辅助帐号不同于将Owner权限授权给其他帐号，因为恢复辅助帐号只能参与帐号恢复过程，它并没有用户帐号的任何权限，无法以用户身份发起任何transaction。

