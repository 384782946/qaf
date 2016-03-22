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

3、目录说明
conf 配置文件
plugin 插件
log 日志文件
data 数据文件