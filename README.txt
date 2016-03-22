1、编译环境
win2010+Qt5.5.1+vs2013

2、VS2013工程配置
默认值：
输出目录 $(SolutionDir)$(Platform)\$(Configuration)\
中间目录 $(Configuration)\
输出文件 $(OutDir)\$(ProjectName).dll

请配置为：
输出目录 $(SolutionDir)bin\$(Configuration)\
中间目录 $(SolutionDir)temp\$(ProjectName)\$(Configuration)\
输出文件 $(OutDir)\$(ProjectName).dll
附加库目录 $(SolutionDir)bin\$(Configuration)\
附加包含目录 $(SolutionDir)xxx

3、目录说明：
bin/conf 配置文件
bin/log 日志文件
bin/data 数据文件
bin/$(Configuration)/plugin 插件目录

4、运行环境：
第三方依赖库放在./lib下，需要拷贝到对应应用程序目录