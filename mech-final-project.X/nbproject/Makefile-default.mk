#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/mech-final-project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/mech-final-project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_CheckEvents.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Framework.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_KeyboardInput.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_PostList.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Queue.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_TattleTale.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Timers.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/AD.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BOARD.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IO_Ports.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/LED.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/pwm.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/RC_Servo.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/serial.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/timers.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Main.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TrackWireService.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/EventChecker.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/Actuators.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TopHSM.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IRService.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BumperService.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/MeanderPt2.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/OlympicPt2SubHSM.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/DisposalSubHSM.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/SnatchSubHSM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o ${OBJECTDIR}/_ext/7063215/ES_Framework.o ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o ${OBJECTDIR}/_ext/7063215/ES_PostList.o ${OBJECTDIR}/_ext/7063215/ES_Queue.o ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o ${OBJECTDIR}/_ext/7063215/ES_Timers.o ${OBJECTDIR}/_ext/7063215/AD.o ${OBJECTDIR}/_ext/7063215/BOARD.o ${OBJECTDIR}/_ext/7063215/IO_Ports.o ${OBJECTDIR}/_ext/7063215/LED.o ${OBJECTDIR}/_ext/7063215/pwm.o ${OBJECTDIR}/_ext/7063215/RC_Servo.o ${OBJECTDIR}/_ext/7063215/serial.o ${OBJECTDIR}/_ext/7063215/timers.o ${OBJECTDIR}/_ext/7063215/ES_Main.o ${OBJECTDIR}/_ext/7063215/TrackWireService.o ${OBJECTDIR}/_ext/7063215/EventChecker.o ${OBJECTDIR}/_ext/7063215/Actuators.o ${OBJECTDIR}/_ext/7063215/TopHSM.o ${OBJECTDIR}/_ext/7063215/IRService.o ${OBJECTDIR}/_ext/7063215/BumperService.o ${OBJECTDIR}/_ext/7063215/MeanderPt2.o ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/7063215/ES_Framework.o.d ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/7063215/ES_PostList.o.d ${OBJECTDIR}/_ext/7063215/ES_Queue.o.d ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o.d ${OBJECTDIR}/_ext/7063215/ES_Timers.o.d ${OBJECTDIR}/_ext/7063215/AD.o.d ${OBJECTDIR}/_ext/7063215/BOARD.o.d ${OBJECTDIR}/_ext/7063215/IO_Ports.o.d ${OBJECTDIR}/_ext/7063215/LED.o.d ${OBJECTDIR}/_ext/7063215/pwm.o.d ${OBJECTDIR}/_ext/7063215/RC_Servo.o.d ${OBJECTDIR}/_ext/7063215/serial.o.d ${OBJECTDIR}/_ext/7063215/timers.o.d ${OBJECTDIR}/_ext/7063215/ES_Main.o.d ${OBJECTDIR}/_ext/7063215/TrackWireService.o.d ${OBJECTDIR}/_ext/7063215/EventChecker.o.d ${OBJECTDIR}/_ext/7063215/Actuators.o.d ${OBJECTDIR}/_ext/7063215/TopHSM.o.d ${OBJECTDIR}/_ext/7063215/IRService.o.d ${OBJECTDIR}/_ext/7063215/BumperService.o.d ${OBJECTDIR}/_ext/7063215/MeanderPt2.o.d ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o.d ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o.d ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o ${OBJECTDIR}/_ext/7063215/ES_Framework.o ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o ${OBJECTDIR}/_ext/7063215/ES_PostList.o ${OBJECTDIR}/_ext/7063215/ES_Queue.o ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o ${OBJECTDIR}/_ext/7063215/ES_Timers.o ${OBJECTDIR}/_ext/7063215/AD.o ${OBJECTDIR}/_ext/7063215/BOARD.o ${OBJECTDIR}/_ext/7063215/IO_Ports.o ${OBJECTDIR}/_ext/7063215/LED.o ${OBJECTDIR}/_ext/7063215/pwm.o ${OBJECTDIR}/_ext/7063215/RC_Servo.o ${OBJECTDIR}/_ext/7063215/serial.o ${OBJECTDIR}/_ext/7063215/timers.o ${OBJECTDIR}/_ext/7063215/ES_Main.o ${OBJECTDIR}/_ext/7063215/TrackWireService.o ${OBJECTDIR}/_ext/7063215/EventChecker.o ${OBJECTDIR}/_ext/7063215/Actuators.o ${OBJECTDIR}/_ext/7063215/TopHSM.o ${OBJECTDIR}/_ext/7063215/IRService.o ${OBJECTDIR}/_ext/7063215/BumperService.o ${OBJECTDIR}/_ext/7063215/MeanderPt2.o ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o

# Source Files
SOURCEFILES=C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_CheckEvents.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Framework.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_KeyboardInput.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_PostList.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Queue.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_TattleTale.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Timers.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/AD.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BOARD.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IO_Ports.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/LED.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/pwm.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/RC_Servo.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/serial.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/timers.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Main.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TrackWireService.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/EventChecker.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/Actuators.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TopHSM.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IRService.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BumperService.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/MeanderPt2.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/OlympicPt2SubHSM.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/DisposalSubHSM.c C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/SnatchSubHSM.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/mech-final-project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="C:\UCSC\mechatronics-final-project\ECE118 Files\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_CheckEvents.c  .generated_files/flags/default/605cd7470a5d8875a7c64bb6e0b504f1761fb3f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_Framework.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Framework.c  .generated_files/flags/default/57cafa77a4cc6df17c647edfa2d4b29984ef2fea .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_Framework.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_KeyboardInput.c  .generated_files/flags/default/2084f2a5bf6ab42569b8cbbd1b121e9c8a8f7674 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_PostList.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_PostList.c  .generated_files/flags/default/543de4b63cbbb3922b5d03464096f742d760c469 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_PostList.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_Queue.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Queue.c  .generated_files/flags/default/36631a15077befbac273ad316ff06f902f6a6c75 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_Queue.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_TattleTale.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_TattleTale.c  .generated_files/flags/default/6a1b21d392b48811a9afb420d08cf933f7a18bc6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_Timers.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Timers.c  .generated_files/flags/default/2fe87c12dfcd05bf6c479ba90a36c1b724e568f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_Timers.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/AD.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/AD.c  .generated_files/flags/default/ec85a18347ec1c0674737563ebb0c7d75ac60f29 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/AD.o.d" -o ${OBJECTDIR}/_ext/7063215/AD.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/BOARD.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BOARD.c  .generated_files/flags/default/6b2fa127f0d76f0293fc71a04cebcb71bc1c3e7c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/BOARD.o.d" -o ${OBJECTDIR}/_ext/7063215/BOARD.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/IO_Ports.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IO_Ports.c  .generated_files/flags/default/4e34b40598ef7783a0b56164a1e134757fe372a6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/7063215/IO_Ports.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/LED.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/LED.c  .generated_files/flags/default/875315ba7f0213dfebd3399a871759f4879b660b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/LED.o.d" -o ${OBJECTDIR}/_ext/7063215/LED.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/pwm.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/pwm.c  .generated_files/flags/default/e61c4b43cf04d8006ab052795b55552099dc9688 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/pwm.o.d" -o ${OBJECTDIR}/_ext/7063215/pwm.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/RC_Servo.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/RC_Servo.c  .generated_files/flags/default/a38e8534cbac51b9d3338eb33ecb9aeb1652d42d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/7063215/RC_Servo.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/serial.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/serial.c  .generated_files/flags/default/98a7ca8c71b6e8d26af67c61d2c23b481bbe1248 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/serial.o.d" -o ${OBJECTDIR}/_ext/7063215/serial.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/timers.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/timers.c  .generated_files/flags/default/f3b054b070839d2100cbe69f0fd2f650feaccf82 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/timers.o.d" -o ${OBJECTDIR}/_ext/7063215/timers.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_Main.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Main.c  .generated_files/flags/default/d55e37165c2724f14cf02a53ec2a532acafc02a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_Main.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_Main.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/TrackWireService.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TrackWireService.c  .generated_files/flags/default/bc36e09942b466b62f62f08705fe4ea3d4ba8c25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/TrackWireService.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/TrackWireService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/TrackWireService.o.d" -o ${OBJECTDIR}/_ext/7063215/TrackWireService.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TrackWireService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/EventChecker.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/EventChecker.c  .generated_files/flags/default/ac46e5260519c6dcd88e1d6ff8224dfd02227f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/EventChecker.o.d" -o ${OBJECTDIR}/_ext/7063215/EventChecker.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/EventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/Actuators.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/Actuators.c  .generated_files/flags/default/8a3a2f714f72ae424d9c9acd098591b0524a9e0f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/Actuators.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/Actuators.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/Actuators.o.d" -o ${OBJECTDIR}/_ext/7063215/Actuators.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/Actuators.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/TopHSM.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TopHSM.c  .generated_files/flags/default/9156906dd2b0a91015407f365352cb84b21ae60d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/TopHSM.o.d" -o ${OBJECTDIR}/_ext/7063215/TopHSM.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TopHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/IRService.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IRService.c  .generated_files/flags/default/c059491ae01382ced5d8fdbd3d376a7009652293 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/IRService.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/IRService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/IRService.o.d" -o ${OBJECTDIR}/_ext/7063215/IRService.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IRService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/BumperService.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BumperService.c  .generated_files/flags/default/64837150af3dcc770515025d095151f0c7b7e7f2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/BumperService.o.d" -o ${OBJECTDIR}/_ext/7063215/BumperService.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BumperService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/MeanderPt2.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/MeanderPt2.c  .generated_files/flags/default/d701e9fa61e2846f8317687c790ead78308f5313 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/MeanderPt2.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/MeanderPt2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/MeanderPt2.o.d" -o ${OBJECTDIR}/_ext/7063215/MeanderPt2.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/MeanderPt2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/OlympicPt2SubHSM.c  .generated_files/flags/default/5cee451d531084d38500ef7983395385550c84ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o.d" -o ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/OlympicPt2SubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/DisposalSubHSM.c  .generated_files/flags/default/30d01e72fb8de904b82c06e03ff1a744ab2abca1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o.d" -o ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/DisposalSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/SnatchSubHSM.c  .generated_files/flags/default/41e051d9733e92d46d93789f4d54009e76a81b87 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o.d" -o ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/SnatchSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_CheckEvents.c  .generated_files/flags/default/867c5273f8a64a09dc739cf560fb0ab9328a0f9b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_CheckEvents.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_Framework.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Framework.c  .generated_files/flags/default/6cd8b29d68a3b13997ffa10101b6aa8b261bba99 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_Framework.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_KeyboardInput.c  .generated_files/flags/default/2b0a7ce07f9d12d7d4429f513e257851a9f891ff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_KeyboardInput.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_PostList.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_PostList.c  .generated_files/flags/default/9021904637a25287c64a3f1ebe5a7cbc0b76dda9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_PostList.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_Queue.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Queue.c  .generated_files/flags/default/d7d6f440f0c8f605cc20d253d2d7e0d48f7fe70b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_Queue.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_TattleTale.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_TattleTale.c  .generated_files/flags/default/f6b8ab7586229b52f7176f9f2ca2c046c017c85b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_TattleTale.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_Timers.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Timers.c  .generated_files/flags/default/aa9d962d80e6bb5461e210d08a59e4c153ce7f63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_Timers.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/AD.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/AD.c  .generated_files/flags/default/c2094dbb38347176cbd5fefd4ca7adc5256716a5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/AD.o.d" -o ${OBJECTDIR}/_ext/7063215/AD.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/BOARD.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BOARD.c  .generated_files/flags/default/3e7779d16e760a5db731bfca665cd0fd5bcbd586 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/BOARD.o.d" -o ${OBJECTDIR}/_ext/7063215/BOARD.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/IO_Ports.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IO_Ports.c  .generated_files/flags/default/e8728cea0ae83a19de6edf25ce8e2072bd15a687 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/7063215/IO_Ports.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/LED.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/LED.c  .generated_files/flags/default/4a72db8bef164b6a7949e02369a9e76b17e4b106 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/LED.o.d" -o ${OBJECTDIR}/_ext/7063215/LED.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/pwm.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/pwm.c  .generated_files/flags/default/bc54e14262fc922a4f5df2d775e51da6261eae2f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/pwm.o.d" -o ${OBJECTDIR}/_ext/7063215/pwm.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/RC_Servo.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/RC_Servo.c  .generated_files/flags/default/d94d1b0b4ea6470957299dc1b3b4eb397f7ead33 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/7063215/RC_Servo.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/serial.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/serial.c  .generated_files/flags/default/74859d1f7d43c8f0428e084952d40571826ceab1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/serial.o.d" -o ${OBJECTDIR}/_ext/7063215/serial.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/timers.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/timers.c  .generated_files/flags/default/6b23afdef3340bdc0f3dcee23193b612a9ba4d2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/timers.o.d" -o ${OBJECTDIR}/_ext/7063215/timers.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/ES_Main.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Main.c  .generated_files/flags/default/dc3ff0185e2c12dd0d6a17fc057a148be6a1ef39 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/ES_Main.o.d" -o ${OBJECTDIR}/_ext/7063215/ES_Main.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/ES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/TrackWireService.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TrackWireService.c  .generated_files/flags/default/88e76d1d6197ea88b6cbc54d5db83b872e0407a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/TrackWireService.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/TrackWireService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/TrackWireService.o.d" -o ${OBJECTDIR}/_ext/7063215/TrackWireService.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TrackWireService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/EventChecker.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/EventChecker.c  .generated_files/flags/default/f32b9e9083137f87f57c0d37f987464dce80df5d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/EventChecker.o.d" -o ${OBJECTDIR}/_ext/7063215/EventChecker.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/EventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/Actuators.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/Actuators.c  .generated_files/flags/default/48c5d3cb84d0fd0c39c39e548abb39fd2843dffc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/Actuators.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/Actuators.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/Actuators.o.d" -o ${OBJECTDIR}/_ext/7063215/Actuators.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/Actuators.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/TopHSM.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TopHSM.c  .generated_files/flags/default/a5c3408523ec13f632c98fb33339654eedb0917d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/TopHSM.o.d" -o ${OBJECTDIR}/_ext/7063215/TopHSM.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/TopHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/IRService.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IRService.c  .generated_files/flags/default/ed7c34df31085f06c9099e84546aa85b1fde772c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/IRService.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/IRService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/IRService.o.d" -o ${OBJECTDIR}/_ext/7063215/IRService.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/IRService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/BumperService.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BumperService.c  .generated_files/flags/default/67e59990e546a8e34fdf6177a686d789f82d0db1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/BumperService.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/BumperService.o.d" -o ${OBJECTDIR}/_ext/7063215/BumperService.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/BumperService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/MeanderPt2.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/MeanderPt2.c  .generated_files/flags/default/3f4bc88806fa3fe551e31569bdc27b29d5b0cb86 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/MeanderPt2.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/MeanderPt2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/MeanderPt2.o.d" -o ${OBJECTDIR}/_ext/7063215/MeanderPt2.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/MeanderPt2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/OlympicPt2SubHSM.c  .generated_files/flags/default/4bfccdcdf53c4cb10504d55eb587a089d1f8447a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o.d" -o ${OBJECTDIR}/_ext/7063215/OlympicPt2SubHSM.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/OlympicPt2SubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/DisposalSubHSM.c  .generated_files/flags/default/1c72baa0af6e921a8d77cbadb1cf5f0f63ade52c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o.d" -o ${OBJECTDIR}/_ext/7063215/DisposalSubHSM.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/DisposalSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o: C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/SnatchSubHSM.c  .generated_files/flags/default/55eb51596f61f3e8b9c45865d9f754d7b7bf9bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/7063215" 
	@${RM} ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DSIMPLESERVICE_TEST -I"." -MP -MMD -MF "${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o.d" -o ${OBJECTDIR}/_ext/7063215/SnatchSubHSM.o C:/UCSC/mechatronics-final-project/ece-118-lucky-charm/mech-final-project.X/SnatchSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/mech-final-project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/UCSC/mechatronics-final-project/ECE118\ Files/bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/mech-final-project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1023,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/mech-final-project.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/UCSC/mechatronics-final-project/ECE118\ Files/bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/mech-final-project.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1023,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/mech-final-project.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
