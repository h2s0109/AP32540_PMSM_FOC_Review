AP32540_PMSM_FOC_motor_control_using_AURIX_TC3xx
==
># Revision history
> Workaround VSCODE
VSCODE doesn`t support recursive intellisense.
replace the below keyword.
MCUCARD_TYPE_PATH
"PmsmFoc_AppKitTft_TC387A.h"
INVERTERCARD_TYPE_PATH
"PmsmFoc_EMotorDrive_v_3_1.h"
MOTOR_TYPE_PATH
"PmsmFoc_Motor_Nanotec_DB42S02.h"

>## Branch: Master
>### V1.0.0: Initial version
> * First version
> * AP32540_PMSM_FOC_motor_control_using_AURIX_TC3xx_v1.0.2
> * .gitignore
> * B_GNUC_TRICORE_PATH:=  C:\Tools\HighTec\toolchains\tricore\v4.9.2.0
> * B_TASKING_TRICORE_PATH= C:\Program Files\TASKING\TriCore v6.3r1
>## Branch: Patch
>### V1.0.1: TFT_DISPLAYMODE
> Add the preprocessor macros
> * #define TFT_DISPLAYMODE
> * #if(TFT_DISPLAYMODE == ENABLED)
>### V1.0.2: ONE_EYEMODE
> Add the preprocessor macros
> * #define ONE_EYEMODE
> * #if(ONE_EYEMODE == ENABLED)
> * /*STEVE: not ONE_EYEMODE but has a dependency with ONE_EYEMODE */
>### V1.0.3: TLF35584_DRIVER
> Add the preprocessor macros
> * /*STEVE: define error TLF35584*/
> * #if(TLF35584_DRIVER == ENABLED)
>### V1.0.4: TLE9180_DRIVER
> Add the preprocessor macros
> * /*STEVE: define error TLE9180*/
> * #if(TLE9180_DRIVER == ENABLED)
>### V1.0.5: TLE9180_DRIVER
> Add the preprocessor macros
> * #if(PHASE_CURRENT_RECONSTRUCTION == USER_LOWSIDE_THREE_SHUNT_WITH_HIGHSIDE_MONITORING)
> * #if(DC_LINK_VOLTAGE_MEASUREMENT == ENABLED)
> * #if(BEMF_MEASUREMENT == ENABLED)
> * #if(POSITION_SENSOR_TYPE == ENCODER)
>### V1.0.6: include-path arrange
> re-arrange the #include
> * Removed not necessary #include
> * #include "Ifx_Types.h"
> * #include "Compilers.h"
> * #include "IfxCpu.h"
> * #include "PmsmFoc_Inverter.h"
> * 
> * #include "IfxEdsadc_Edsadc.h"
> * #include "IfxEdsadc_reg.h"
> * #include "IfxEdsadc_regdef.h"
> * #include "IfxEdsadc_bf.h"
> * 
> * #include "IfxEvadc_reg.h"
> * #include "IfxEvadc_regdef.h"
> * #include "IfxEvadc_bf.h"
> * #include "IfxEvadc.h"
> * What is the role of Role of PmsmFoc_Interface.h?
> * Mixed usage with PmsmFoc_Functions.h,PmsmFoc_StateMachine.h
> * change #if !defined(MOTOR_CONTROL_H) -> #ifndef MOTOR_CONTROL_H
> * PmsmFoc_StateMachine.c bug fix, add the comment.
>## Branch: Dbgctrl_dev
>### V1.0.6.1: Debug control function
> * on the develop.
>### V1.0.6.2: Debug control function: compile test complete
> * comile test completed.
>### V1.0.6.3: Debug control function: improve the whole functionality.
> * complete the whole debug function test on board.
> * implement STM, GTM debug stop
> * OS overlap priority change.
> * StateMachine_motorStop need re-design.