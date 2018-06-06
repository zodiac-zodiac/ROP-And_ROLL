#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "pin.H"

ofstream OutFile;

static UINT64 ret = 0;
static UINT64 call = 0;
int Tid = 0 ;
stringstream s  ;

VOID ret_count() { ret++; }
VOID call_count() { call++; }


VOID Instruction(INS ins, VOID *v)
{

if(PIN_IsApplicationThread())
{
 
Tid = PIN_GetTid() ;


if(INS_IsRet(ins)  ){
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)ret_count, IARG_END);

cout<< " RET count : " << ret << " CALL count : "<< call << " Current Opcode : " << INS_Mnemonic(ins) << "/" << INS_Opcode(ins)<< endl ;

}


if(INS_IsCall(ins)  ){
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)call_count, IARG_END);

cout<< " RET count : " << ret << " CALL count : "<< call << " Current Opcode : " << INS_Mnemonic(ins) << "/" << INS_Opcode(ins)<< endl ;

}


}

}

VOID Fini(INT32 code, VOID *v)
{

 
}


INT32 Usage()
{

    
    return -1;
}



int main(int argc, char * argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();



    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
