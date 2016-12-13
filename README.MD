基于Qt应用程序开发的通用软件实例、提供日志管理、对象管理、属性编辑、运行配置等常用功能
，框架采用插件式开发，降低模块间耦合性，未来还会加入python脚本的支持，以方便应用灵活拓展，
本人水平有限，欢迎批评指正。

###1、开发环境
Qt5.5.1+msvc2013

###2、工程配置
输出目录 $(SolutionDir)bin\$(Configuration)\
中间目录 $(SolutionDir)temp\$(ProjectName)\$(Configuration)\
目标文件名 $(ProjectName)d
目标文件扩展名 .dll
输出文件 $(OutDir)\$(TargetName)$(TargetExt)
附加库目录 $(SolutionDir)lib
附加包含目录 $(SolutionDir)xxx

某些项目需添加生成后事件：
copy $(TargetPath) $(SolutionDir)bin\$(Configuration)
copy $(OutDir)$(TargetName).pdb $(SolutionDir)bin\$(Configuration)
copy $(ProjectDir)*.h $(SolutionDir)include\$(ProjectName)

###3、输出目录结果说明：
conf 配置文件
log 日志文件
lang 翻译文件
style 样式
data 公用数据文件
$(Configuration) 主程序目录
$(Configuration)/plugin 插件目录

###4、运行环境：
第三方依赖库放在./lib下，需要拷贝到对应应用程序目录

###5、预处理器定义
SINGLETON_APPLICTION		应用程序单实例
WITHOUT_LOG					消除日志

###6、功能列表
内存托管
常用Qt扩展类
AwesomeFont支持
网络传输
配置文件管理
插件管理
界面可定制化
日志管理

###7、更新日志