/* Generated from testy.scm by the CHICKEN compiler
   http://www.call-cc.org
   2014-05-13 03:11
   Version 4.8.0.5 (stability/4.8.0) (rev 5bd53ac)
   linux-unix-gnu-x86-64 [ 64bit manyargs dload ptables ]
   compiled 2013-10-03 on aeryn.xorinia.dim (Darwin)
   command line: testy.scm -to-stdout -raw -to-stdout -explicit-use
   used units: 
*/

#include "chicken.h"

static C_PTABLE_ENTRY *create_ptable(void);

static C_TLS C_word lf[2];
static double C_possibly_force_alignment;
static C_char C_TLS li0[] C_aligned={C_lihdr(0,0,10),40,116,111,112,108,101,118,101,108,41,0,0,0,0,0,0};


C_noret_decl(C_toplevel)
C_externexport void C_ccall C_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_12)
static void C_ccall f_12(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(tr2)
static void C_fcall tr2(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2(C_proc2 k){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
(k)(2,t0,t1);}

/* toplevel */
static C_TLS int toplevel_initialized=0;
C_main_entry_point
C_noret_decl(toplevel_trampoline)
static void C_fcall toplevel_trampoline(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall toplevel_trampoline(void *dummy){
C_toplevel(2,C_SCHEME_UNDEFINED,C_restore);}

void C_ccall C_toplevel(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word *a;
if(toplevel_initialized) C_kontinue(t1,C_SCHEME_UNDEFINED);
else C_toplevel_entry(C_text("toplevel"));
C_check_nursery_minimum(3);
if(!C_demand(3)){
C_save(t1);
C_reclaim((void*)toplevel_trampoline,NULL);}
toplevel_initialized=1;
if(!C_demand_2(20)){
C_save(t1);
C_rereclaim2(20*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,2);
lf[0]=C_h_intern(&lf[0],3,"foo");
lf[1]=C_h_intern(&lf[1],7,"display");
C_register_lf2(lf,2,create_ptable());
t2=C_set_block_item(lf[0] /* foo */,0,C_fix(46));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_12,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_trace("testy.scm:2: display");
((C_proc3)C_fast_retrieve_proc(*((C_word*)lf[1]+1)))(3,*((C_word*)lf[1]+1),t3,C_fast_retrieve(lf[0]));}

/* k11 */
static void C_ccall f_12(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[3] = {
{"toplevel:testy_2escm",(void*)C_toplevel},
{"f_12:testy_2escm",(void*)f_12},
{NULL,NULL}};
#endif

static C_PTABLE_ENTRY *create_ptable(void){
#ifdef C_ENABLE_PTABLES
return ptable;
#else
return NULL;
#endif
}

/*
o|folded constant expression: (+ (quote 3) (quote 43)) 
o|removed binding forms: 1 
o|contracted procedure: k8 
o|removed binding forms: 1 
o|substituted constant variable: r9 
o|removed binding forms: 1 
*/
/* end of file */
