#include "set_run.h"
#include "scan.h"
#include "edge.h"
#include "led.h"
#include "key.h"
#include "sound.h"
#include "delay.h"
#include "drive.h"

#include "scan_120.set"			// 120 steps, 65.0237 cm/s
#include "rush_120.set"     	// 120 steps, 65.0237 cm/s

#include "rush_25s.set"			// 250 steps, 95.3298 cm/s slower setting
#include "rush_250.set"			// 250 steps, 95.3298 cm/s



// Function Pointer to set RUN.
void (*set_run_rush)();
void (*set_run_scan)();

// SCAN /////////////////////////////////////////
// common (auxiliary)
	int 	INFO_iSPD_SCAN;
	#ifndef	DISABLE_OVERSTP
	int		INFO_overSTP;
	#endif
// sFX
	int		INFO_sFX_aMOD; // 0:Accl / 1:Unif
	int		INFO_sFX_aSPD;
	int		INFO_sFX_aMAX;
// sRX
	int 	INFO_sRX_inSTP;
	int 	INFO_sRX_tPOS;
	int 	INFO_sRX_aSTP;
	int 	INFO_sRX_uSTP;
	int 	INFO_sRX_dPL;
	int		INFO_sRX_dPR;
	int 	INFO_sRX_outSTP;
// sLX
	int 	INFO_sLX_inSTP;
	int 	INFO_sLX_tPOS;
	int 	INFO_sLX_aSTP;
	int 	INFO_sLX_uSTP;
	int 	INFO_sLX_dPL;
	int		INFO_sLX_dPR;
	int 	INFO_sLX_outSTP;
// INTER ////////////////////////////////////////
// dPx (dPL/dPR or dPR/dPL) = 0/3 fixed!!
// SCAN -> RUSH
// irFF		Forward
	int 	INFO_irFF_outSTP;
// irFL		in 45
	int		INFO_irFL_inSTP;
	int		INFO_irFL_aSTP;
	int		INFO_irFL_uSTP;
	int		INFO_irFL_outSTP;
// irFR		in 45
	int		INFO_irFR_inSTP;
	int		INFO_irFR_aSTP;
	int		INFO_irFR_uSTP;
	int		INFO_irFR_outSTP;
// irLF		in 90
	int 	INFO_irLF_outSTP;
// irRF		in 90
	int 	INFO_irRF_outSTP;
// irLL		in 135
	int		INFO_irLL_inSTP;
	int		INFO_irLL_aSTP;
	int		INFO_irLL_uSTP;
	int		INFO_irLL_outSTP;
// irRR		in 135
	int		INFO_irRR_inSTP;
	int		INFO_irRR_aSTP;
	int		INFO_irRR_uSTP;
	int		INFO_irRR_outSTP;
// irLR		twist in 45
	int		INFO_irLR_inSTP;
	int		INFO_irLR_a1STP;
	int		INFO_irLR_u1STP;
	int		INFO_irLR_a2STP;
	int		INFO_irLR_u2STP;
	int		INFO_irLR_outSTP;
	int 	INFO_irLR_dPL;
	int		INFO_irLR_dPR;
// irRL		twist in 45
	int		INFO_irRL_inSTP;
	int		INFO_irRL_a1STP;
	int		INFO_irRL_u1STP;
	int		INFO_irRL_a2STP;
	int		INFO_irRL_u2STP;
	int		INFO_irRL_outSTP;
	int 	INFO_irRL_dPL;
	int		INFO_irRL_dPR;
// RUSH -> SCAN
// isFF		Forward
	int		INFO_isFF_outSTP;
// isLF		out 45
	int		INFO_isLF_inSTP;
	int		INFO_isLF_aSTP;
	int		INFO_isLF_uSTP;
	int		INFO_isLF_outSTP;
// isRF		out 45
	int		INFO_isRF_inSTP;
	int		INFO_isRF_aSTP;
	int		INFO_isRF_uSTP;
	int		INFO_isRF_outSTP;
// isFL		out 90
	int		INFO_isFL_inSTP;
// isFR		out 90
	int		INFO_isFR_inSTP;
// isLL		out 135
	int		INFO_isLL_inSTP;
	int		INFO_isLL_aSTP;
	int		INFO_isLL_uSTP;
	int		INFO_isLL_outSTP;
// isRR		out 135
	int		INFO_isRR_inSTP;
	int		INFO_isRR_aSTP;
	int		INFO_isRR_uSTP;
	int		INFO_isRR_outSTP;
// isLR		twist out 45
	int		INFO_isLR_inSTP;
	int		INFO_isLR_a1STP;
	int		INFO_isLR_u1STP;
	int		INFO_isLR_a2STP;
	int		INFO_isLR_u2STP;
	int		INFO_isLR_outSTP;
	int 	INFO_isLR_dPL;
	int		INFO_isLR_dPR;
// isRL		twist out 45
	int		INFO_isRL_inSTP;
	int		INFO_isRL_a1STP;
	int		INFO_isRL_u1STP;
	int		INFO_isRL_a2STP;
	int		INFO_isRL_u2STP;
	int		INFO_isRL_outSTP;
	int 	INFO_isRL_dPL;
	int		INFO_isRL_dPR;

// RUSH /////////////////////////////////////////
// common (auxiliary)
	int 	INFO_iSPD_RUSH;
	int 	INFO_iSPD_SRUSH;		// Start Blk
// aSFRL
	int		INFO_aSFRL_inSTP;
	int	    INFO_aSFRL_aSTP;
	int		INFO_aSFRL_uSTP;
	int		INFO_aSFRL_dPL;
	int		INFO_aSFRL_dPR;
// aSFRF
	int		INFO_aSFRF_inSTP;
	int	    INFO_aSFRF_aSTP;
	int		INFO_aSFRF_uSTP;
	int		INFO_aSFRF_dPL;
	int		INFO_aSFRF_dPR;
// aSFRRL
	int		INFO_aSFRRL_inSTP;
	int	    INFO_aSFRRL_aSTP;
	int		INFO_aSFRRL_uSTP;
	int		INFO_aSFRRL_dPL;
	int		INFO_aSFRRL_dPR;
// rFF
	int		INFO_rFF_aMAX;
// rFRF
	int 	INFO_rFRF_inSTP;
	int 	INFO_rFRF_aSTP;
	int 	INFO_rFRF_uSTP;
	int 	INFO_rFRF_dPL;
	int		INFO_rFRF_dPR;
	int 	INFO_rFRF_outSTP;
// rFLF
	int 	INFO_rFLF_inSTP;
	int 	INFO_rFLF_aSTP;
	int 	INFO_rFLF_uSTP;
	int 	INFO_rFLF_dPL;
	int		INFO_rFLF_dPR;
	int 	INFO_rFLF_outSTP;
// rFRRF
	int 	INFO_rFRRF_inSTP;
	int 	INFO_rFRRF_aSTP;
	int 	INFO_rFRRF_uSTP;
	int 	INFO_rFRRF_dPL;
	int		INFO_rFRRF_dPR;
	int 	INFO_rFRRF_outSTP;
// rFLLF
	int 	INFO_rFLLF_inSTP;
	int 	INFO_rFLLF_aSTP;
	int 	INFO_rFLLF_uSTP;
	int 	INFO_rFLLF_dPL;
	int		INFO_rFLLF_dPR;
	int 	INFO_rFLLF_outSTP;
// rFR
	int 	INFO_rFR_inSTP;
	int 	INFO_rFR_aSTP;
	int 	INFO_rFR_uSTP;
	int 	INFO_rFR_dPL;
	int		INFO_rFR_dPR;
	int 	INFO_rFR_outSTP;
// rFL
	int 	INFO_rFL_inSTP;
	int 	INFO_rFL_aSTP;
	int 	INFO_rFL_uSTP;
	int 	INFO_rFL_dPL;
	int		INFO_rFL_dPR;
	int 	INFO_rFL_outSTP;
// rFRR
	int 	INFO_rFRR_inSTP;
	int 	INFO_rFRR_aSTP;
	int 	INFO_rFRR_uSTP;
	int 	INFO_rFRR_dPL;
	int		INFO_rFRR_dPR;
	int 	INFO_rFRR_outSTP;
// rFLL
	int 	INFO_rFLL_inSTP;
	int 	INFO_rFLL_aSTP;
	int 	INFO_rFLL_uSTP;
	int 	INFO_rFLL_dPL;
	int		INFO_rFLL_dPR;
	int 	INFO_rFLL_outSTP;
// rRF
	int 	INFO_rRF_inSTP;
	int 	INFO_rRF_aSTP;
	int 	INFO_rRF_uSTP;
	int 	INFO_rRF_dPL;
	int		INFO_rRF_dPR;
	int 	INFO_rRF_outSTP;
// rLF
	int 	INFO_rLF_inSTP;
	int 	INFO_rLF_aSTP;
	int 	INFO_rLF_uSTP;
	int 	INFO_rLF_dPL;
	int		INFO_rLF_dPR;
	int 	INFO_rLF_outSTP;
// rRRF
	int 	INFO_rRRF_inSTP;
	int 	INFO_rRRF_aSTP;
	int 	INFO_rRRF_uSTP;
	int 	INFO_rRRF_dPL;
	int		INFO_rRRF_dPR;
	int 	INFO_rRRF_outSTP;
// rLLF
	int 	INFO_rLLF_inSTP;
	int 	INFO_rLLF_aSTP;
	int 	INFO_rLLF_uSTP;
	int 	INFO_rLLF_dPL;
	int		INFO_rLLF_dPR;
	int 	INFO_rLLF_outSTP;
// rLL
	int 	INFO_rLL_inSTP;
	int 	INFO_rLL_aSTP;
	int 	INFO_rLL_uSTP;
	int 	INFO_rLL_dPL;
	int		INFO_rLL_dPR;
	int 	INFO_rLL_outSTP;
// rRR
	int 	INFO_rRR_inSTP;
	int 	INFO_rRR_aSTP;
	int 	INFO_rRR_uSTP;
	int 	INFO_rRR_dPL;
	int		INFO_rRR_dPR;
	int 	INFO_rRR_outSTP;
// rDF (rLR/rRL)
	int		INFO_rDF_aMAX;



