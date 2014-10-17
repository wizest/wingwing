#ifndef	__SET_RUN_H
#define __SET_RUN_H

	// scan
	#define		set_run_scan_normal() 		set_run_scan_120()
	#define		set_run_iscan_normal()		set_run_iscan_120()

	// rush
	#define 	set_run_rush_slow()			set_run_rush_120()
	#define		set_run_rush_normal()		set_run_rush_120()
	#define		set_run_rush_fast()			set_run_rush_250s()
	#define		set_run_rush_very_fast()	set_run_rush_250()

	// scan
	extern	void set_run_scan_120();
	extern	void set_run_iscan_120();

	// rush
	extern	void set_run_rush_120();
	extern	void set_run_rush_250s();
	extern 	void set_run_rush_250();

	// Function Pointer to set RUN.
	extern void (*set_run_rush)();
	extern void (*set_run_scan)();



// SCAN /////////////////////////////////////////
// common
	extern	int		INFO_iSPD_SCAN;
	#ifndef DISABLE_OVERSTP
	extern	int		INFO_overSTP;
	#endif
// sFX
	extern	int		INFO_sFX_aMOD;
	extern	int		INFO_sFX_aSPD;
	extern	int		INFO_sFX_aMAX;
// sRX
	extern	int 	INFO_sRX_inSTP;
	extern	int 	INFO_sRX_tPOS;
	extern	int 	INFO_sRX_aSTP;
	extern	int 	INFO_sRX_uSTP;
	extern	int 	INFO_sRX_dPL;
	extern	int		INFO_sRX_dPR;
	extern	int 	INFO_sRX_outSTP;
// sLX
	extern	int 	INFO_sLX_inSTP;
	extern	int 	INFO_sLX_tPOS;
	extern	int 	INFO_sLX_aSTP;
	extern	int 	INFO_sLX_uSTP;
	extern	int 	INFO_sLX_dPL;
	extern	int		INFO_sLX_dPR;
	extern	int 	INFO_sLX_outSTP;

// INTER ////////////////////////////////////////
// dPx (dPL/dPR or dPR/dPL) = 0/3 fixed!!
// SCAN -> RUSH
// irFF		Forward
	extern	int 	INFO_irFF_outSTP;
// irFL		in 45
	extern	int		INFO_irFL_inSTP;
	extern	int		INFO_irFL_aSTP;
	extern	int		INFO_irFL_uSTP;
	extern	int		INFO_irFL_outSTP;
// irFR		in 45
	extern	int		INFO_irFR_inSTP;
	extern	int		INFO_irFR_aSTP;
	extern	int		INFO_irFR_uSTP;
	extern	int		INFO_irFR_outSTP;
// irLF		in 90
	extern	int 	INFO_irLF_outSTP;
// irRF		in 90
	extern	int 	INFO_irRF_outSTP;
// irLL		in 135
	extern	int		INFO_irLL_inSTP;
	extern	int		INFO_irLL_aSTP;
	extern	int		INFO_irLL_uSTP;
	extern	int		INFO_irLL_outSTP;
// irRR		in 135
	extern	int		INFO_irRR_inSTP;
	extern	int		INFO_irRR_aSTP;
	extern	int		INFO_irRR_uSTP;
	extern	int		INFO_irRR_outSTP;
// irLR		twist in 45
	extern	int		INFO_irLR_inSTP;
	extern	int		INFO_irLR_a1STP;
	extern	int		INFO_irLR_u1STP;
	extern	int		INFO_irLR_a2STP;
	extern	int		INFO_irLR_u2STP;
	extern	int		INFO_irLR_outSTP;
	extern	int 	INFO_irLR_dPL;
	extern	int 	INFO_irLR_dPR;
// irRL		twist in 45
	extern	int		INFO_irRL_inSTP;
	extern	int		INFO_irRL_a1STP;
	extern	int		INFO_irRL_u1STP;
	extern	int		INFO_irRL_a2STP;
	extern	int		INFO_irRL_u2STP;
	extern	int		INFO_irRL_outSTP;
	extern	int 	INFO_irRL_dPL;
	extern	int 	INFO_irRL_dPR;
// RUSH -> SCAN
// isFF		Forward
	extern	int		INFO_isFF_outSTP;
// isLF		out 45
	extern	int		INFO_isLF_inSTP;
	extern	int		INFO_isLF_aSTP;
	extern	int		INFO_isLF_uSTP;
	extern	int		INFO_isLF_outSTP;
// isRF		out 45
	extern	int		INFO_isRF_inSTP;
	extern	int		INFO_isRF_aSTP;
	extern	int		INFO_isRF_uSTP;
	extern	int		INFO_isRF_outSTP;
// isFL		out 90
	extern	int		INFO_isFL_inSTP;
// isFR		out 90
	extern	int		INFO_isFR_inSTP;
// isLL		out 135
	extern	int		INFO_isLL_inSTP;
	extern	int		INFO_isLL_aSTP;
	extern	int		INFO_isLL_uSTP;
	extern	int		INFO_isLL_outSTP;
// isRR		out 135
	extern	int		INFO_isRR_inSTP;
	extern	int		INFO_isRR_aSTP;
	extern	int		INFO_isRR_uSTP;
	extern	int		INFO_isRR_outSTP;
// isLR		twist out 45
	extern	int		INFO_isLR_inSTP;
	extern	int		INFO_isLR_a1STP;
	extern	int		INFO_isLR_u1STP;
	extern	int		INFO_isLR_a2STP;
	extern	int		INFO_isLR_u2STP;
	extern	int		INFO_isLR_outSTP;
	extern	int 	INFO_isLR_dPL;
	extern	int 	INFO_isLR_dPR;
// isRL		twist out 45
	extern	int		INFO_isRL_inSTP;
	extern	int		INFO_isRL_a1STP;
	extern	int		INFO_isRL_u1STP;
	extern	int		INFO_isRL_a2STP;
	extern	int		INFO_isRL_u2STP;
	extern	int		INFO_isRL_outSTP;
	extern	int 	INFO_isRL_dPL;
	extern	int 	INFO_isRL_dPR;


// RUSH /////////////////////////////////////////
// common (auxiliary)
	extern	int 	INFO_iSPD_RUSH;
	extern	int 	INFO_iSPD_SRUSH;	// start blk
// aSFRL
	extern	int		INFO_aSFRL_inSTP;
	extern	int	    INFO_aSFRL_aSTP;
	extern	int		INFO_aSFRL_uSTP;
	extern	int		INFO_aSFRL_dPL;
	extern	int		INFO_aSFRL_dPR;
// aSFRF
	extern	int		INFO_aSFRF_inSTP;
	extern	int	    INFO_aSFRF_aSTP;
	extern	int		INFO_aSFRF_uSTP;
	extern	int		INFO_aSFRF_dPL;
	extern	int		INFO_aSFRF_dPR;
// aSFRRL
	extern	int		INFO_aSFRRL_inSTP;
	extern	int	    INFO_aSFRRL_aSTP;
	extern	int		INFO_aSFRRL_uSTP;
	extern	int		INFO_aSFRRL_dPL;
	extern	int		INFO_aSFRRL_dPR;
// rFF
	extern 	int		INFO_rFF_aMAX;
// rFRF
	extern 	int 	INFO_rFRF_inSTP;
	extern 	int 	INFO_rFRF_aSTP;
	extern 	int 	INFO_rFRF_uSTP;
	extern 	int 	INFO_rFRF_dPL;
	extern 	int		INFO_rFRF_dPR;
	extern 	int 	INFO_rFRF_outSTP;
// rFLF
	extern 	int 	INFO_rFLF_inSTP;
	extern 	int 	INFO_rFLF_aSTP;
	extern 	int 	INFO_rFLF_uSTP;
	extern 	int 	INFO_rFLF_dPL;
	extern 	int		INFO_rFLF_dPR;
	extern 	int 	INFO_rFLF_outSTP;
// rFRRF
	extern 	int 	INFO_rFRRF_inSTP;
	extern 	int 	INFO_rFRRF_aSTP;
	extern 	int 	INFO_rFRRF_uSTP;
	extern 	int 	INFO_rFRRF_dPL;
	extern 	int		INFO_rFRRF_dPR;
	extern 	int 	INFO_rFRRF_outSTP;
// rFLLF
	extern 	int 	INFO_rFLLF_inSTP;
	extern 	int 	INFO_rFLLF_aSTP;
	extern 	int 	INFO_rFLLF_uSTP;
	extern 	int 	INFO_rFLLF_dPL;
	extern 	int		INFO_rFLLF_dPR;
	extern 	int 	INFO_rFLLF_outSTP;
// rFR
	extern 	int 	INFO_rFR_inSTP;
	extern 	int 	INFO_rFR_aSTP;
	extern 	int 	INFO_rFR_uSTP;
	extern 	int 	INFO_rFR_dPL;
	extern 	int		INFO_rFR_dPR;
	extern 	int 	INFO_rFR_outSTP;
// rFL
	extern 	int 	INFO_rFL_inSTP;
	extern 	int 	INFO_rFL_aSTP;
	extern 	int 	INFO_rFL_uSTP;
	extern 	int 	INFO_rFL_dPL;
	extern 	int		INFO_rFL_dPR;
	extern 	int 	INFO_rFL_outSTP;
// rFRR
	extern 	int 	INFO_rFRR_inSTP;
	extern 	int 	INFO_rFRR_aSTP;
	extern 	int 	INFO_rFRR_uSTP;
	extern 	int 	INFO_rFRR_dPL;
	extern 	int		INFO_rFRR_dPR;
	extern 	int 	INFO_rFRR_outSTP;
// rFLL
	extern 	int 	INFO_rFLL_inSTP;
	extern 	int 	INFO_rFLL_aSTP;
	extern 	int 	INFO_rFLL_uSTP;
	extern 	int 	INFO_rFLL_dPL;
	extern 	int		INFO_rFLL_dPR;
	extern 	int 	INFO_rFLL_outSTP;
// rRF
	extern 	int 	INFO_rRF_inSTP;
	extern 	int 	INFO_rRF_aSTP;
	extern 	int 	INFO_rRF_uSTP;
	extern 	int 	INFO_rRF_dPL;
	extern 	int		INFO_rRF_dPR;
	extern 	int 	INFO_rRF_outSTP;
// rLF
	extern 	int 	INFO_rLF_inSTP;
	extern 	int 	INFO_rLF_aSTP;
	extern 	int 	INFO_rLF_uSTP;
	extern 	int 	INFO_rLF_dPL;
	extern 	int		INFO_rLF_dPR;
	extern 	int 	INFO_rLF_outSTP;
// rRRF
	extern 	int 	INFO_rRRF_inSTP;
	extern 	int 	INFO_rRRF_aSTP;
	extern 	int 	INFO_rRRF_uSTP;
	extern 	int 	INFO_rRRF_dPL;
	extern 	int		INFO_rRRF_dPR;
	extern 	int 	INFO_rRRF_outSTP;
// rLLF
	extern 	int 	INFO_rLLF_inSTP;
	extern 	int 	INFO_rLLF_aSTP;
	extern 	int 	INFO_rLLF_uSTP;
	extern 	int 	INFO_rLLF_dPL;
	extern 	int		INFO_rLLF_dPR;
	extern 	int 	INFO_rLLF_outSTP;
// rLL
	extern 	int 	INFO_rLL_inSTP;
	extern 	int 	INFO_rLL_aSTP;
	extern 	int 	INFO_rLL_uSTP;
	extern 	int 	INFO_rLL_dPL;
	extern 	int		INFO_rLL_dPR;
	extern 	int 	INFO_rLL_outSTP;
// rRR
	extern 	int 	INFO_rRR_inSTP;
	extern 	int 	INFO_rRR_aSTP;
	extern 	int 	INFO_rRR_uSTP;
	extern 	int 	INFO_rRR_dPL;
	extern 	int		INFO_rRR_dPR;
	extern 	int 	INFO_rRR_outSTP;
// rDF (rLR/rRL)
	extern	int		INFO_rDF_aMAX;

#endif