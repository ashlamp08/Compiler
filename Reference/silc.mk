##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=silc
ConfigurationName      :=Debug
WorkspacePath          := "G:\work\silc"
ProjectPath            := "G:\work\silc"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Suraj
Date                   :=24/01/2016
CodeLitePath           :="G:\Program Files\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="silc.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=G:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/sim-2_lex.yy.c$(ObjectSuffix) $(IntermediateDirectory)/sim-2_simulator.c$(ObjectSuffix) $(IntermediateDirectory)/Stage 3_Interpreter.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stage 3_test.c$(ObjectSuffix) $(IntermediateDirectory)/Stage 4_Interpreter.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stage 8_compiler.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stage 8_symbolTable.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(ObjectSuffix) $(IntermediateDirectory)/evenOdd.cpp$(ObjectSuffix) $(IntermediateDirectory)/expression.cpp$(ObjectSuffix) $(IntermediateDirectory)/expression_lex.cpp$(ObjectSuffix) $(IntermediateDirectory)/exptree.cpp$(ObjectSuffix) $(IntermediateDirectory)/in2post.cpp$(ObjectSuffix) $(IntermediateDirectory)/in2post.tab.c$(ObjectSuffix) $(IntermediateDirectory)/in2post_lex.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/infix2postfixString.cpp$(ObjectSuffix) $(IntermediateDirectory)/infix2postfixString_lex.cpp$(ObjectSuffix) $(IntermediateDirectory)/int2post.cpp$(ObjectSuffix) $(IntermediateDirectory)/lex.yy.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/sim-2_lex.yy.c$(ObjectSuffix): sim-2/lex.yy.c $(IntermediateDirectory)/sim-2_lex.yy.c$(DependSuffix)
	$(CC) $(SourceSwitch) "G:/work/silc/sim-2/lex.yy.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sim-2_lex.yy.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sim-2_lex.yy.c$(DependSuffix): sim-2/lex.yy.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sim-2_lex.yy.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sim-2_lex.yy.c$(DependSuffix) -MM "sim-2/lex.yy.c"

$(IntermediateDirectory)/sim-2_lex.yy.c$(PreprocessSuffix): sim-2/lex.yy.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sim-2_lex.yy.c$(PreprocessSuffix) "sim-2/lex.yy.c"

$(IntermediateDirectory)/sim-2_simulator.c$(ObjectSuffix): sim-2/simulator.c $(IntermediateDirectory)/sim-2_simulator.c$(DependSuffix)
	$(CC) $(SourceSwitch) "G:/work/silc/sim-2/simulator.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sim-2_simulator.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sim-2_simulator.c$(DependSuffix): sim-2/simulator.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sim-2_simulator.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sim-2_simulator.c$(DependSuffix) -MM "sim-2/simulator.c"

$(IntermediateDirectory)/sim-2_simulator.c$(PreprocessSuffix): sim-2/simulator.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sim-2_simulator.c$(PreprocessSuffix) "sim-2/simulator.c"

$(IntermediateDirectory)/Stage 3_Interpreter.cpp$(ObjectSuffix): Stage 3/Interpreter.cpp $(IntermediateDirectory)/Stage 3_Interpreter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 3/Interpreter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 3_Interpreter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 3_Interpreter.cpp$(DependSuffix): Stage 3/Interpreter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 3_Interpreter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 3_Interpreter.cpp$(DependSuffix) -MM "Stage 3/Interpreter.cpp"

$(IntermediateDirectory)/Stage 3_Interpreter.cpp$(PreprocessSuffix): Stage 3/Interpreter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 3_Interpreter.cpp$(PreprocessSuffix) "Stage 3/Interpreter.cpp"

$(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(ObjectSuffix): Stage 3/Interpreter_lex.cpp $(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 3/Interpreter_lex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(DependSuffix): Stage 3/Interpreter_lex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(DependSuffix) -MM "Stage 3/Interpreter_lex.cpp"

$(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(PreprocessSuffix): Stage 3/Interpreter_lex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 3_Interpreter_lex.cpp$(PreprocessSuffix) "Stage 3/Interpreter_lex.cpp"

$(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(ObjectSuffix): Stage 3/syntaxTree.cpp $(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 3/syntaxTree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(DependSuffix): Stage 3/syntaxTree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(DependSuffix) -MM "Stage 3/syntaxTree.cpp"

$(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(PreprocessSuffix): Stage 3/syntaxTree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 3_syntaxTree.cpp$(PreprocessSuffix) "Stage 3/syntaxTree.cpp"

$(IntermediateDirectory)/Stage 3_test.c$(ObjectSuffix): Stage 3/test.c $(IntermediateDirectory)/Stage 3_test.c$(DependSuffix)
	$(CC) $(SourceSwitch) "G:/work/silc/Stage 3/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 3_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 3_test.c$(DependSuffix): Stage 3/test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 3_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 3_test.c$(DependSuffix) -MM "Stage 3/test.c"

$(IntermediateDirectory)/Stage 3_test.c$(PreprocessSuffix): Stage 3/test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 3_test.c$(PreprocessSuffix) "Stage 3/test.c"

$(IntermediateDirectory)/Stage 4_Interpreter.cpp$(ObjectSuffix): Stage 4/Interpreter.cpp $(IntermediateDirectory)/Stage 4_Interpreter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 4/Interpreter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 4_Interpreter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 4_Interpreter.cpp$(DependSuffix): Stage 4/Interpreter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 4_Interpreter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 4_Interpreter.cpp$(DependSuffix) -MM "Stage 4/Interpreter.cpp"

$(IntermediateDirectory)/Stage 4_Interpreter.cpp$(PreprocessSuffix): Stage 4/Interpreter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 4_Interpreter.cpp$(PreprocessSuffix) "Stage 4/Interpreter.cpp"

$(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(ObjectSuffix): Stage 4/Interpreter_lex.cpp $(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 4/Interpreter_lex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(DependSuffix): Stage 4/Interpreter_lex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(DependSuffix) -MM "Stage 4/Interpreter_lex.cpp"

$(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(PreprocessSuffix): Stage 4/Interpreter_lex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 4_Interpreter_lex.cpp$(PreprocessSuffix) "Stage 4/Interpreter_lex.cpp"

$(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(ObjectSuffix): Stage 4/syntaxTree.cpp $(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 4/syntaxTree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(DependSuffix): Stage 4/syntaxTree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(DependSuffix) -MM "Stage 4/syntaxTree.cpp"

$(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(PreprocessSuffix): Stage 4/syntaxTree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 4_syntaxTree.cpp$(PreprocessSuffix) "Stage 4/syntaxTree.cpp"

$(IntermediateDirectory)/Stage 8_compiler.cpp$(ObjectSuffix): Stage 8/compiler.cpp $(IntermediateDirectory)/Stage 8_compiler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 8/compiler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 8_compiler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 8_compiler.cpp$(DependSuffix): Stage 8/compiler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 8_compiler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 8_compiler.cpp$(DependSuffix) -MM "Stage 8/compiler.cpp"

$(IntermediateDirectory)/Stage 8_compiler.cpp$(PreprocessSuffix): Stage 8/compiler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 8_compiler.cpp$(PreprocessSuffix) "Stage 8/compiler.cpp"

$(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(ObjectSuffix): Stage 8/compiler_lex.cpp $(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 8/compiler_lex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(DependSuffix): Stage 8/compiler_lex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(DependSuffix) -MM "Stage 8/compiler_lex.cpp"

$(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(PreprocessSuffix): Stage 8/compiler_lex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 8_compiler_lex.cpp$(PreprocessSuffix) "Stage 8/compiler_lex.cpp"

$(IntermediateDirectory)/Stage 8_symbolTable.cpp$(ObjectSuffix): Stage 8/symbolTable.cpp $(IntermediateDirectory)/Stage 8_symbolTable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 8/symbolTable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 8_symbolTable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 8_symbolTable.cpp$(DependSuffix): Stage 8/symbolTable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 8_symbolTable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 8_symbolTable.cpp$(DependSuffix) -MM "Stage 8/symbolTable.cpp"

$(IntermediateDirectory)/Stage 8_symbolTable.cpp$(PreprocessSuffix): Stage 8/symbolTable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 8_symbolTable.cpp$(PreprocessSuffix) "Stage 8/symbolTable.cpp"

$(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(ObjectSuffix): Stage 8/syntaxTree.cpp $(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/Stage 8/syntaxTree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(DependSuffix): Stage 8/syntaxTree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(DependSuffix) -MM "Stage 8/syntaxTree.cpp"

$(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(PreprocessSuffix): Stage 8/syntaxTree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stage 8_syntaxTree.cpp$(PreprocessSuffix) "Stage 8/syntaxTree.cpp"

$(IntermediateDirectory)/evenOdd.cpp$(ObjectSuffix): evenOdd.cpp $(IntermediateDirectory)/evenOdd.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/evenOdd.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/evenOdd.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/evenOdd.cpp$(DependSuffix): evenOdd.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/evenOdd.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/evenOdd.cpp$(DependSuffix) -MM "evenOdd.cpp"

$(IntermediateDirectory)/evenOdd.cpp$(PreprocessSuffix): evenOdd.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/evenOdd.cpp$(PreprocessSuffix) "evenOdd.cpp"

$(IntermediateDirectory)/expression.cpp$(ObjectSuffix): expression.cpp $(IntermediateDirectory)/expression.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/expression.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/expression.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/expression.cpp$(DependSuffix): expression.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/expression.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/expression.cpp$(DependSuffix) -MM "expression.cpp"

$(IntermediateDirectory)/expression.cpp$(PreprocessSuffix): expression.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/expression.cpp$(PreprocessSuffix) "expression.cpp"

$(IntermediateDirectory)/expression_lex.cpp$(ObjectSuffix): expression_lex.cpp $(IntermediateDirectory)/expression_lex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/expression_lex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/expression_lex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/expression_lex.cpp$(DependSuffix): expression_lex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/expression_lex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/expression_lex.cpp$(DependSuffix) -MM "expression_lex.cpp"

$(IntermediateDirectory)/expression_lex.cpp$(PreprocessSuffix): expression_lex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/expression_lex.cpp$(PreprocessSuffix) "expression_lex.cpp"

$(IntermediateDirectory)/exptree.cpp$(ObjectSuffix): exptree.cpp $(IntermediateDirectory)/exptree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/exptree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/exptree.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/exptree.cpp$(DependSuffix): exptree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/exptree.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/exptree.cpp$(DependSuffix) -MM "exptree.cpp"

$(IntermediateDirectory)/exptree.cpp$(PreprocessSuffix): exptree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/exptree.cpp$(PreprocessSuffix) "exptree.cpp"

$(IntermediateDirectory)/in2post.cpp$(ObjectSuffix): in2post.cpp $(IntermediateDirectory)/in2post.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/in2post.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/in2post.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/in2post.cpp$(DependSuffix): in2post.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/in2post.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/in2post.cpp$(DependSuffix) -MM "in2post.cpp"

$(IntermediateDirectory)/in2post.cpp$(PreprocessSuffix): in2post.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/in2post.cpp$(PreprocessSuffix) "in2post.cpp"

$(IntermediateDirectory)/in2post.tab.c$(ObjectSuffix): in2post.tab.c $(IntermediateDirectory)/in2post.tab.c$(DependSuffix)
	$(CC) $(SourceSwitch) "G:/work/silc/in2post.tab.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/in2post.tab.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/in2post.tab.c$(DependSuffix): in2post.tab.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/in2post.tab.c$(ObjectSuffix) -MF$(IntermediateDirectory)/in2post.tab.c$(DependSuffix) -MM "in2post.tab.c"

$(IntermediateDirectory)/in2post.tab.c$(PreprocessSuffix): in2post.tab.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/in2post.tab.c$(PreprocessSuffix) "in2post.tab.c"

$(IntermediateDirectory)/in2post_lex.cpp$(ObjectSuffix): in2post_lex.cpp $(IntermediateDirectory)/in2post_lex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/in2post_lex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/in2post_lex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/in2post_lex.cpp$(DependSuffix): in2post_lex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/in2post_lex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/in2post_lex.cpp$(DependSuffix) -MM "in2post_lex.cpp"

$(IntermediateDirectory)/in2post_lex.cpp$(PreprocessSuffix): in2post_lex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/in2post_lex.cpp$(PreprocessSuffix) "in2post_lex.cpp"

$(IntermediateDirectory)/infix2postfixString.cpp$(ObjectSuffix): infix2postfixString.cpp $(IntermediateDirectory)/infix2postfixString.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/infix2postfixString.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/infix2postfixString.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/infix2postfixString.cpp$(DependSuffix): infix2postfixString.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/infix2postfixString.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/infix2postfixString.cpp$(DependSuffix) -MM "infix2postfixString.cpp"

$(IntermediateDirectory)/infix2postfixString.cpp$(PreprocessSuffix): infix2postfixString.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/infix2postfixString.cpp$(PreprocessSuffix) "infix2postfixString.cpp"

$(IntermediateDirectory)/infix2postfixString_lex.cpp$(ObjectSuffix): infix2postfixString_lex.cpp $(IntermediateDirectory)/infix2postfixString_lex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/infix2postfixString_lex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/infix2postfixString_lex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/infix2postfixString_lex.cpp$(DependSuffix): infix2postfixString_lex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/infix2postfixString_lex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/infix2postfixString_lex.cpp$(DependSuffix) -MM "infix2postfixString_lex.cpp"

$(IntermediateDirectory)/infix2postfixString_lex.cpp$(PreprocessSuffix): infix2postfixString_lex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/infix2postfixString_lex.cpp$(PreprocessSuffix) "infix2postfixString_lex.cpp"

$(IntermediateDirectory)/int2post.cpp$(ObjectSuffix): int2post.cpp $(IntermediateDirectory)/int2post.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/work/silc/int2post.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/int2post.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/int2post.cpp$(DependSuffix): int2post.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/int2post.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/int2post.cpp$(DependSuffix) -MM "int2post.cpp"

$(IntermediateDirectory)/int2post.cpp$(PreprocessSuffix): int2post.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/int2post.cpp$(PreprocessSuffix) "int2post.cpp"

$(IntermediateDirectory)/lex.yy.c$(ObjectSuffix): lex.yy.c $(IntermediateDirectory)/lex.yy.c$(DependSuffix)
	$(CC) $(SourceSwitch) "G:/work/silc/lex.yy.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lex.yy.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lex.yy.c$(DependSuffix): lex.yy.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lex.yy.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lex.yy.c$(DependSuffix) -MM "lex.yy.c"

$(IntermediateDirectory)/lex.yy.c$(PreprocessSuffix): lex.yy.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lex.yy.c$(PreprocessSuffix) "lex.yy.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


