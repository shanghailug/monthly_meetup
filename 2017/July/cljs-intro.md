
# ClojureScript 介绍

----

# 关于我

* ChenYong, @题叶, @jiyinyiyong
* 前端开发者, 饿了么, Teambition
* React, ClojureScript

----

# Clojure 是什么

* <http://clojure.org>
* Lisp 方言, 动态语言, macros
* 发明于 2007 年, 现代化的编程语言
* 函数式编程, 不可变数据
* Atoms/Refs 的并发编程
* 编译到 JVM Bytecode, 使用 Jar 包和命名空间

----

# ClojureScript 是什么?

* Clojure, 编译到 JavaScript
* 通过 Google Closure Compiler 生成代码
* 代码热替换功能
* <http://clojurescript.org/>

----

# 有哪些语言特性

* [ClojureScript Syntax in 15 minutes](https://github.com/shaunlebron/ClojureScript-Syntax-in-15-minutes/blob/master/README.zh.md)
* [learnxinyminutes Clojure](https://learnxinyminutes.com/docs/clojure/)
* <http://cljs.info/cheatsheet>
* <http://cljs-book.clj.im>

更多...

----

# Interop

<http://www.spacjer.com/blog/2014/09/12/clojurescript-javascript-interop/>

----

# 工具链

* Build Tasks: Lein / Boot
* React bindings: Om / Reagent / Rum
* REPL: Planck / [Lumo](https://github.com/anmonteiro/lumo)
* Compiler wrapper: [shadow-cljs](https://github.com/thheller/shadow-cljs)

----

# Demo

* REPL
* cljs-basics

基本的代码的演示, 基于 [Lumo](https://github.com/anmonteiro/lumo)

----

# 为什么要研究 ClojureScript

跟前端的技术栈作对比

* 语言设计, 对于数据有更清晰的概念, immutability, atom
* 强调纯函数, 便于进行热替换
* 强大的 DSL 能力
* 同时 immutability 提供了更多优化的空间

----

# 社区

* Clojurians(Slack)
* Reddit/Clojure
* Twitter
* clojureverse.org
* clojure-china.org

----

# npm 生态

* 自动推断引用的外部代码
* npm-deps 复用 npm 模块
* Code Splitting

官网 News 或者 <https://anmonteiro.com/>


----

# Demo

基于 [shadow-cljs](https://github.com/thheller/shadow-cljs)

* 基于热替换的 Node.js 命令行开发
* 基于热替换的测试代码
* 基于热替换的网页开发

(连接大屏幕可能性能问题更明显)

----

# [Cumulo Editor](https://github.com/Cirru/cumulo-editor)(私货)

通过编辑器和 Macro 来编写 Clojure(Script)

----

Thanks
