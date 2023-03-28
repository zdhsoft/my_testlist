# nest笔记十一：typeorm连表查询

## 概述
- [nestjs系列笔记](https://zdhsoft.blog.csdn.net/article/details/121746302)

- 之前的笔记：[nest记笔五：使用TypeORM连接mysql](https://zdhsoft.blog.csdn.net/article/details/121746239)，与 [nest笔记十：typeorm使用经验小结](https://blog.csdn.net/zdhsoft/article/details/127024360)可以使用typeorm的基本功能。随着开发的深入，很多已经满足不了要求了，特别是涉及到连表查询的时候，已经不够用了，这里重点是对连表查询。

- 写这小结的时候，typeorm已经更新0.3.12了, 与之前0.2.x相比，变化蛮大的。这里的内容也是针对0.3.10及以上的版本。使用0.3.12好像有些bug没有解决。所以还是退回到 0.3.10。

## 使用typeorm的装饰器
- 首先是定义关系
下面是一组关系装饰器
|名称|说明|
|:---|:---|
| JoinColumn | 定义了关系的哪一侧包含带有外键的连接列 |
| JoinTable | 用于“多对多”关系，并描述"junction"表的连接列 |
| ManyToMany | 多对多是一种 A 包含多个 B 实例，而 B 包含多个 A 实例的关系。 |
| ManyToOne |多对一是指 A 包含一个 B 实例的关系，但 B 只包含多个 A 实例 |
| OneToMany |多对一是指 A 包含多个 B 实例的关系，但 B 只包含一个 A 实例 |
| OneToOne | 一对一是一种 A 只包含一个 B 实例，而 B 只包含一个 A 实例的关系。|
| RelationCount | 已经\@deprecated了 |
| RelationId | 将特定关系的 id（或 id）加载到属性中 |

### JoinColumn
- 定义了关系的哪一侧包含带有外键的连接列
### JoinTable
- 用于“多对多”关系，并描述"junction"表的连接列
### ManyToMany
### ManyToOne
### OneToMany
### OneToOne
### RelationId




 