#include <unordered_set>
#include "eudplibGlobals.h"

std::unordered_set<std::string> builtinConstSet = {
        "Accumulate", "Action", "Add", "All", "AllPlayers", "AlliedVictory",
        "Allies", "Ally", "Always", "Assignable2List", "AtLeast", "AtMost",
        "Attack", "Bring", "Buildings", "CenterView", "Clear", "Cleared",
        "Command", "CommandLeast", "CommandLeastAt", "CommandMost",
        "CommandMostAt", "Comment", "CompressPayload", "Condition", "ConstExpr",
        "CountdownTimer", "CreatePayload", "CreateUnit",
        "CreateUnitWithProperties", "CtrlStruOpener", "CurrentPlayer", "Custom",
        "DBString", "Db", "Deaths", "Defeat", "Disable", "Disabled",
        "DisplayExtText", "DisplayText", "DoActions", "Draw", "EPD", "EPError",
        "EPSFinder", "EPSLoader", "EPS_SetDebug", "EP_SetRValueStrictMode",
        "EUDAnd", "EUDArray", "EUDBinaryMax", "EUDBinaryMin", "EUDBranch",
        "EUDBreak", "EUDBreakIf", "EUDBreakIfNot", "EUDByteReader",
        "EUDByteWriter", "EUDClearNamespace", "EUDContinue", "EUDContinueIf",
        "EUDContinueIfNot", "EUDCreateBlock", "EUDCreateVariables", "EUDDoEvents",
        "EUDElse", "EUDElseIf", "EUDElseIfNot", "EUDEndExecuteOnce", "EUDEndIf",
        "EUDEndInfLoop", "EUDEndLoopN", "EUDEndPlayerLoop", "EUDEndSwitch",
        "EUDEndWhile", "EUDExecuteOnce", "EUDFunc", "EUDFuncN", "EUDFuncPtr",
        "EUDGetBlockList", "EUDGetLastBlock", "EUDGetLastBlockOfName", "EUDGrp",
        "EUDIf", "EUDIfNot", "EUDInfLoop", "EUDIsContinuePointSet", "EUDJump",
        "EUDJumpIf", "EUDJumpIfNot", "EUDLightVariable", "EUDLoopBullet",
        "EUDLoopList", "EUDLoopN", "EUDLoopRange", "EUDLoopSprite",
        "EUDLoopTrigger", "EUDLoopUnit", "EUDMethod", "EUDNot", "EUDObject",
        "EUDOnStart", "EUDOr", "EUDPeekBlock", "EUDPlayerLoop", "EUDPopBlock",
        "EUDRegisterObjectToNamespace", "EUDRegistered", "EUDReturn", "EUDSCAnd",
        "EUDSCOr", "EUDSetContinuePoint", "EUDStack", "EUDStruct", "EUDSwitch",
        "EUDSwitchCase", "EUDSwitchDefault", "EUDTernary", "EUDTypedFunc",
        "EUDTypedFuncPtr", "EUDTypedMethod", "EUDVArray", "EUDVariable",
        "EUDWhile", "EUDWhileNot", "ElapsedTime", "Enable", "EncodeAIScript",
        "EncodeAllyStatus", "EncodeComparison", "EncodeCount", "EncodeLocation",
        "EncodeModifier", "EncodeOrder", "EncodePlayer", "EncodePropState",
        "EncodeProperty", "EncodeResource", "EncodeScore", "EncodeString",
        "EncodeSwitch", "EncodeSwitchAction", "EncodeSwitchState", "EncodeUnit",
        "Enemy", "Exactly", "ExprProxy", "FlattenList", "Foes", "Force1",
        "Force2", "Force3", "Force4", "Forward", "Gas", "GetChkTokenized",
        "GetEUDNamespace", "GetFirstTrigTrigger", "GetLastTrigTrigger",
        "GetLocationIndex", "GetObjectAddr", "GetPlayerInfo", "GetPropertyIndex",
        "GetStringIndex", "GetSwitchIndex", "GetTriggerCounter", "GetUnitIndex",
        "GiveUnits", "HighestScore", "IsEUDVariable", "IsMapdataInitalized",
        "KillUnit", "KillUnitAt", "Kills", "KillsAndRazings",
        "LeaderBoardComputerPlayers", "LeaderBoardControl",
        "LeaderBoardControlAt", "LeaderBoardGoalControl",
        "LeaderBoardGoalControlAt", "LeaderBoardGoalKills",
        "LeaderBoardGoalResources", "LeaderBoardGoalScore", "LeaderBoardGreed",
        "LeaderBoardKills", "LeaderBoardResources", "LeaderBoardScore",
        "LeastKills", "LeastResources", "List2Assignable", "LoadMap",
        "LowestScore", "MPQAddFile", "MPQAddWave", "Memory", "MemoryEPD",
        "MinimapPing", "ModifyUnitEnergy", "ModifyUnitHangarCount",
        "ModifyUnitHitPoints", "ModifyUnitResourceAmount", "ModifyUnitShields",
        "MostKills", "MostResources", "Move", "MoveLocation", "MoveUnit",
        "MuteUnitSpeech", "NeutralPlayers", "Never", "NextTrigger",
        "NonAlliedVictoryPlayers", "Opponents", "Order", "Ore", "OreAndGas", "P1",
        "P10", "P11", "P12", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9",
        "PRT_SetInliningRate", "PRT_SkipPayloadRelocator", "PTrigger", "Patrol",
        "PauseGame", "PauseTimer", "PlayWAV", "Player1", "Player10", "Player11",
        "Player12", "Player2", "Player3", "Player4", "Player5", "Player6",
        "Player7", "Player8", "Player9", "PopTriggerScope", "PreserveTrigger",
        "PushTriggerScope", "QueueGameCommand", "QueueGameCommand_RightClick",
        "QueueGameCommand_Select", "Random", "RawTrigger", "Razings",
        "RegisterCreatePayloadCallback", "RemoveUnit", "RemoveUnitAt",
        "RlocInt_C", "RunAIScript", "RunAIScriptAt", "RunTrigTrigger",
        "SCMD2Text", "SaveMap", "Score", "SeqCompute", "Set", "SetAllianceStatus",
        "SetCountdownTimer", "SetCurrentPlayer", "SetDeaths", "SetDoodadState",
        "SetInvincibility", "SetMemory", "SetMemoryEPD", "SetMissionObjectives",
        "SetNextPtr", "SetNextScenario", "SetResources", "SetScore", "SetSwitch",
        "SetTo", "SetVariables", "Subtract", "Switch", "TBL", "TalkingPortrait",
        "Toggle", "Total", "Transmission", "TrgAIScript", "TrgAllyStatus",
        "TrgComparison", "TrgCount", "TrgLocation", "TrgModifier", "TrgOrder",
        "TrgPlayer", "TrgPropState", "TrgProperty", "TrgResource", "TrgScore",
        "TrgString", "TrgSwitch", "TrgSwitchAction", "TrgSwitchState", "TrgUnit",
        "TrigTriggerBegin", "TrigTriggerEnd", "Trigger", "UnMuteUnitSpeech",
        "UnitProperty", "Units", "UnitsAndBuildings", "UnpauseGame",
        "UnpauseTimer", "VProc", "Victory", "Wait", "afterTriggerExec", "b2i1",
        "b2i2", "b2i4", "b2u", "beforeTriggerExec", "cachedfunc", "createEncoder",
        "ep_assert", "epsCompile", "eudplibVersion", "f_atan2", "f_bitand",
        "f_bitlshift", "f_bitnand", "f_bitnor", "f_bitnot", "f_bitnxor",
        "f_bitor", "f_bitrshift", "f_bitsplit", "f_bitxor", "f_blockpatch_epd",
        "f_bread", "f_bread_epd", "f_bwrite", "f_bwrite_epd", "f_dbstr_adddw",
        "f_dbstr_addptr", "f_dbstr_addstr", "f_dbstr_print", "f_div",
        "f_dwadd_cp", "f_dwadd_epd", "f_dwbreak", "f_dwbreak2", "f_dwepdread_cp",
        "f_dwepdread_epd", "f_dwepdread_epd_safe", "f_dwpatch_epd", "f_dwrand",
        "f_dwread", "f_dwread_cp", "f_dwread_epd", "f_dwread_epd_safe",
        "f_dwsubtract_cp", "f_dwsubtract_epd", "f_dwwrite", "f_dwwrite_cp",
        "f_dwwrite_epd", "f_epdread_cp", "f_epdread_epd", "f_epdread_epd_safe",
        "f_flagread_epd", "f_getcurpl", "f_getseed", "f_getuserplayerid",
        "f_initextstr", "f_lengthdir", "f_memcpy", "f_mul", "f_playerexist",
        "f_rand", "f_randomize", "f_repmovsd_epd", "f_setcurpl", "f_simpleprint",
        "f_sqrt", "f_srand", "f_strcmp", "f_strcpy", "f_unpatchall", "f_wread",
        "f_wread_epd", "f_wwrite", "f_wwrite_epd", "find_data_file", "hptr",
        "i2b1", "i2b2", "i2b4", "isStrict", "isUnproxyInstance", "onPluginStart",
        "selftype", "setStrict", "settings", "u2b", "u2utf8", "unProxy",
};

bool isBuiltinConst(std::string& name) {
    if(name == "True" || name == "true") {
        name = "True";
        return true;
    }

    else if(name == "False" || name == "false") {
        name = "False";
        return true;
    }
    else if (name == "None") return true;

    else {
        return builtinConstSet.find(name) != builtinConstSet.end();
    }
}
