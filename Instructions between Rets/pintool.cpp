
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "pin.H"

static int icount = 0;
int Tid = 0 ;
stringstream Out_name  ;

VOID Ins_Count() {


 std::ofstream Out_file;
 Out_name.str("Thread_") ;
 Out_name << Tid  ; 
 Out_file.open(Out_name.str().c_str(), std::ios_base::app);

// Log INS count

 Out_file  << " RET DETECTED ! INS Count : " << icount+1  << endl;  
 Out_file.close() ;

// Reset icount
 icount = 0 ;

}


VOID Get_Index_Pointers( const CONTEXT * ctxt  )
{

  std::ofstream Out_file ;
 Out_name.str("Thread_") ;
 Out_name << Tid ; 
 Out_file.open(Out_name.str().c_str(), std::ios_base::app);
 ADDRINT EIP = (ADDRINT)PIN_GetContextReg( ctxt, REG_INST_PTR );
  icount++;


 Out_file <<  " EIP = " << hex << EIP << dec << endl;

 Out_file.close() ;

}

VOID count() { icount++; 
}


VOID Instruction(INS ins, VOID *v)
{

if(PIN_IsApplicationThread() )
{

Tid = PIN_GetTid() ;

if(INS_IsRet(ins) ){ 

INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)Ins_Count ,IARG_END);

}
else{
INS_InsertCall( ins, IPOINT_BEFORE, (AFUNPTR)Get_Index_Pointers, IARG_CONTEXT, IARG_END);
}

}}

// Exit
VOID Fini(INT32 code, VOID *v)
{

}

INT32 Usage()
{
    cerr << "This tool counts the number of instructions executed between RET " << endl;
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
