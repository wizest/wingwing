#ifndef __AM188ES_H
#   include <AM188ES.H>
#endif

#ifndef __run_h
#define __run_h

extern void 			init_run();

extern unsigned int 	get_run();	// if empty, return 0;
extern void 			put_run(void (*run_type)());
extern void 			clr_run();

#define RUN_QUEUE_SIZE 		270
extern void          	(*run)();
extern void          	(*run_queue[RUN_QUEUE_SIZE])();
extern unsigned int		run_fptr;
extern unsigned int		run_rptr;

// RUNs header ////////////////////////////////////////////////////////

	// s : scanning RUN
	// r : rushing RUN
	// i : inter RUN
	// a : auxiliary RUN

	// scan.run
		extern 	void	run_sFX();		// F
		extern  void	run_sRX();		// R
		extern  void	run_sBX();		// B
		extern  void	run_sLX();		// L

	// rush.run
		// orthogonal -> orthoganal
		extern 	void	run_rFF();		// Orthogonal Forward
		extern 	void	run_rFLF();		// L90
		extern 	void	run_rFRF();		// R90
		extern 	void	run_rFLLF();	// L180
		extern 	void	run_rFRRF();	// R180
		// rush_O2O.run
			extern 	void 	run_rush_O2O(int tDIR, int inSTP,int aSTP,int uSTP,int dPL,int dPR,int outSTP);
			extern 	void	run_rush_DF();

		// orthogonal -> diagonal
		extern 	void	run_rFL();		// L45 in
		extern 	void	run_rFR();		// R45 in
		extern 	void	run_rFLL();		// L135 in
		extern 	void	run_rFRR();		// R135 in
		// rush_O2D.run
			extern 	void 	run_rush_O2D(int tDIR, int inSTP,int aSTP,int uSTP,int dPL,int dPR,int outSTP);

		// diagonal -> orthogonal
		extern 	void	run_rLF();		// L45 out
		extern 	void	run_rRF();		// R45 out
		extern 	void	run_rLLF();		// L135 out
		extern 	void	run_rRRF();		// R135 out
		// rush_D2O.run
			extern 	void 	run_rush_D2O(int tDIR, int inSTP,int aSTP,int uSTP,int dPL,int dPR,int outSTP);

		// diagonal -> diagonal
		extern 	void	run_rLR();		// Diagonal Forward
		extern 	void	run_rRL();		// Diagonal Forward
		extern 	void	run_rLL();		// Diagonal L90
		extern 	void	run_rRR();		// Diagonal R90
		// rush_D2D.run
			extern 	void 	run_rush_D2D(int tDIR, int inSTP,int aSTP,int uSTP,int dPL,int dPR,int outSTP);
			extern	void	run_rush_DF();

	// inter.run
		// scan -> rush
		extern  void	run_irFF();		// Forward in
		extern  void	run_irFL();		// L45 in
		extern  void	run_irFR();		// R45 in
		extern  void	run_irLF();		// L90 in
		extern  void	run_irRF();		// R90 in
		extern  void	run_irLL();		// L135 in
		extern  void	run_irRR();		// R135 in
		extern  void	run_irLR();		// L45 twist in
		extern  void	run_irRL();		// R45 twist in


		// otherwise virtual RUNs (impossible RUNs)

		// rush -> scan
		extern  void	run_isFF();		// Forward out
		extern  void	run_isLF();		// L45 out
		extern  void	run_isRF();		// R45 out
		extern  void	run_isFL();   	// L90 out
		extern  void	run_isFR();		// R90 out
		extern  void	run_isLL();		// L135 out
		extern  void	run_isRR();		// R135 out
		extern  void	run_isLR();		// R45 twist out	not L!
		extern  void	run_isRL();		// L45 twist out	not R!

	// auxil.run
		// for direct calling Auxiliary pattern
		extern  void	run_aTURN();	// turn180 in start block
		extern 	void	run_aFHF();		// finishing half block
		extern  void	run_aCHF();		// connecting half block
		extern 	void	run_aSHF();		// starting half scan block
		extern	void 	run_aSACCL();	// first accl rush block

		extern	void 	run_aSFF();     // starting rush block
		extern 	void 	run_aSFRL();    // starting rush block
		extern 	void 	run_aSFRF();    // starting rush block
		extern 	void 	run_aSFRRL();   // starting rush block

///////////////////////////////////////////////////////////////////////

#endif