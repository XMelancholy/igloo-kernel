/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * License Terms: GNU General Public License v2
 *
 * Authors: Sundar Iyer <sundar.iyer@stericsson.com>
 *          Bengt Jonsson <bengt.g.jonsson@stericsson.com>
 *
 * MOP500 board specific initialization for regulators
 */
#include <linux/kernel.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/ab8500.h>
#include "board-mop500-regulators.h"

#ifdef CONFIG_REGULATOR_FIXED_VOLTAGE
/*
 * GPIO regulator controlled by the ab8500 GPIO16
 */
static struct regulator_consumer_supply gpio_wlan_vbat_consumers[] = {
	/* for cg2900 chip */
	REGULATOR_SUPPLY("vdd", "cg2900-uart.0"),
	/* for cw1200 chip */
	REGULATOR_SUPPLY("vdd", "cw1200_wlan"),
};

struct regulator_init_data gpio_wlan_vbat_regulator = {
	.constraints = {
		.name = "WLAN-VBAT",
		.min_uV = 3600000,
		.max_uV = 3600000,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies = ARRAY_SIZE(gpio_wlan_vbat_consumers),
	.consumer_supplies = gpio_wlan_vbat_consumers,
};

/*
 * GPIO regulator controlled by the ab8500 GPIO26
 */
static struct regulator_consumer_supply gpio_en_3v3_consumers[] = {
	/* for LAN chip */
	REGULATOR_SUPPLY("vdd33a", "smsc911x.0"),
};

struct regulator_init_data gpio_en_3v3_regulator = {
	.constraints = {
		.name = "EN-3V3",
		.min_uV = 3300000,
		.max_uV = 3300000,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies = ARRAY_SIZE(gpio_en_3v3_consumers),
	.consumer_supplies = gpio_en_3v3_consumers,
};
#endif

/*
 * TPS61052 regulator
 */
static struct regulator_consumer_supply tps61052_vaudio_consumers[] = {
	/*
	 * Boost converter supply to raise voltage on audio speaker, this
	 * is actually connected to three pins, VInVhfL (left amplifier)
	 * VInVhfR (right amplifier) and VIntDClassInt - all three must
	 * be connected to the same voltage.
	 */
	REGULATOR_SUPPLY("vintdclassint", "ab8500-codec.0"),
};

struct regulator_init_data tps61052_regulator = {
	.constraints = {
		.name = "vaudio-hf",
		.min_uV = 4500000,
		.max_uV = 4500000,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies = ARRAY_SIZE(tps61052_vaudio_consumers),
	.consumer_supplies = tps61052_vaudio_consumers,
};

static struct regulator_consumer_supply ab8500_vaux1_consumers[] = {
	/* lps001wp baromenter i2c dev name is 2-005c
	 * maybe change that in the driver, like for lsm303dlh drivers
	 */
	REGULATOR_SUPPLY("vdd", "2-005c"),
	/* Main display, u8500 R3 uib */
	REGULATOR_SUPPLY("vddi", "mcde_disp_sony_acx424akp.0"),
	/* Main display, u8500 uib and ST uib */
	REGULATOR_SUPPLY("vdd1", "samsung_s6d16d0.0"),
	/* Secondary display, ST uib */
	REGULATOR_SUPPLY("vdd1", "samsung_s6d16d0.1"),
	/* SFH7741 proximity sensor */
	REGULATOR_SUPPLY("vcc", "gpio-keys.0"),
	/* BH1780GLS ambient light sensor */
	REGULATOR_SUPPLY("vcc", "2-0029"),
	/* lsm303dlh accelerometer */
	REGULATOR_SUPPLY("vdd", "lsm303dlh.0"),
	/* lsm303dlh magnetometer */
	REGULATOR_SUPPLY("vdd", "lsm303dlh.1"),
	/* Rohm BU21013 Touchscreen devices */
	REGULATOR_SUPPLY("avdd", "3-005c"),
	REGULATOR_SUPPLY("avdd", "3-005d"),
	/* Synaptics RMI4 Touchscreen device */
	REGULATOR_SUPPLY("vdd", "3-004b"),
	/* L3G4200D Gyroscope device */
	REGULATOR_SUPPLY("vdd", "l3g4200d"),
	/* Proximity and Hal sensor device */
	REGULATOR_SUPPLY("vdd", "sensor1p.0"),
	/* Ambient light sensor device */
	REGULATOR_SUPPLY("vdd", "3-0029"),
	/* Cypress TrueTouch Touchscreen device */
	REGULATOR_SUPPLY("vcpin", "spi8.0"),
	/* Camera device */
	REGULATOR_SUPPLY("vaux12v5", "mmio_camera"),
};

static struct regulator_consumer_supply ab8500_vaux2_consumers[] = {
	/* On-board eMMC power */
	REGULATOR_SUPPLY("vmmc", "sdi4"),
	/* AB8500 audio codec */
	REGULATOR_SUPPLY("vcc-N2158", "ab8500-codec.0"),
	/* AB8500 accessory detect 1 */
	REGULATOR_SUPPLY("vcc-N2158", "ab8500-acc-det.0"),
	/* AB8500 Tv-out device */
	REGULATOR_SUPPLY("vcc-N2158", "mcde_tv_ab8500.4"),
	/* AV8100 HDMI device */
	REGULATOR_SUPPLY("vcc-N2158", "av8100_hdmi.3"),
};

static struct regulator_consumer_supply ab8500_vaux3_consumers[] = {
	/* External MMC slot power */
	REGULATOR_SUPPLY("vmmc", "sdi0"),
};

static struct regulator_consumer_supply ab8500_vtvout_consumers[] = {
	/* TV-out DENC supply */
	REGULATOR_SUPPLY("vtvout", "ab8500-denc.0"),
	/* Internal general-purpose ADC */
	REGULATOR_SUPPLY("vddadc", "ab8500-gpadc.0"),
	/* ADC for charger */
	REGULATOR_SUPPLY("vddadc", "ab8500-charger.0"),
	/* AB8500 Tv-out device */
	REGULATOR_SUPPLY("vtvout", "mcde_tv_ab8500.4"),
};

static struct regulator_consumer_supply ab8500_vaudio_consumers[] = {
	/* AB8500 audio codec device */
	REGULATOR_SUPPLY("v-audio", NULL),
};

static struct regulator_consumer_supply ab8500_vamic1_consumers[] = {
	/* AB8500 audio codec device */
	REGULATOR_SUPPLY("v-amic1", NULL),
};

static struct regulator_consumer_supply ab8500_vamic2_consumers[] = {
	/* AB8500 audio codec device */
	REGULATOR_SUPPLY("v-amic2", NULL),
};

static struct regulator_consumer_supply ab8500_vdmic_consumers[] = {
	/* AB8500 audio codec device */
	REGULATOR_SUPPLY("v-dmic", NULL),
};

static struct regulator_consumer_supply ab8500_vintcore_consumers[] = {
	/* SoC core supply, no device */
	REGULATOR_SUPPLY("v-intcore", NULL),
	/* USB Transceiver */
	REGULATOR_SUPPLY("vddulpivio18", "ab8500-usb.0"),
};

static struct regulator_consumer_supply ab8500_vana_consumers[] = {
	/* DB8500 DSI */
	REGULATOR_SUPPLY("vdddsi1v2", "mcde"),
	/* DB8500 CSI */
	REGULATOR_SUPPLY("vddcsi1v2", "mmio_camera"),
};

static struct regulator_consumer_supply ab8500_sysclkreq_2_consumers[] = {
	/* CG2900 device */
	REGULATOR_SUPPLY("gbf_1v8", "cg2900-uart.0"),
};

static struct regulator_consumer_supply ab8500_sysclkreq_4_consumers[] = {
	/* CW1200 device */
	REGULATOR_SUPPLY("wlan_1v8", "cw1200_wlan.0"),
};

/* ab8500 regulator register initialization */
static struct ab8500_regulator_reg_init ab8500_reg_init[] = {
	/*
	 * VanaRequestCtrl          = HP/LP depending on VxRequest
	 * VpllRequestCtrl          = HP/LP depending on VxRequest
	 * VextSupply1RequestCtrl   = HP/LP depending on VxRequest
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUREQUESTCTRL2,       0xfc, 0x00),
	/*
	 * VextSupply2RequestCtrl   = HP/LP depending on VxRequest
	 * VextSupply3RequestCtrl   = HP/LP depending on VxRequest
	 * Vaux1RequestCtrl         = HP/LP depending on VxRequest
	 * Vaux2RequestCtrl         = HP/LP depending on VxRequest
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUREQUESTCTRL3,       0xff, 0x00),
	/*
	 * Vaux3RequestCtrl         = HP/LP depending on VxRequest
	 * SwHPReq                  = Control through SWValid disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUREQUESTCTRL4,       0x07, 0x00),
	/*
	 * Vsmps1SysClkReq1HPValid  = enabled
	 * Vsmps2SysClkReq1HPValid  = enabled
	 * Vsmps3SysClkReq1HPValid  = enabled
	 * VanaSysClkReq1HPValid    = disabled
	 * VpllSysClkReq1HPValid    = enabled
	 * Vaux1SysClkReq1HPValid   = disabled
	 * Vaux2SysClkReq1HPValid   = disabled
	 * Vaux3SysClkReq1HPValid   = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUSYSCLKREQ1HPVALID1, 0xff, 0x17),
	/*
	 * VextSupply1SysClkReq1HPValid = disabled
	 * VextSupply2SysClkReq1HPValid = disabled
	 * VextSupply3SysClkReq1HPValid = SysClkReq1 controlled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUSYSCLKREQ1HPVALID2, 0x70, 0x40),
	/*
	 * VanaHwHPReq1Valid        = disabled
	 * Vaux1HwHPreq1Valid       = disabled
	 * Vaux2HwHPReq1Valid       = disabled
	 * Vaux3HwHPReqValid        = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUHWHPREQ1VALID1,     0xe8, 0x00),
	/*
	 * VextSupply1HwHPReq1Valid = disabled
	 * VextSupply2HwHPReq1Valid = disabled
	 * VextSupply3HwHPReq1Valid = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUHWHPREQ1VALID2,     0x07, 0x00),
	/*
	 * VanaHwHPReq2Valid        = disabled
	 * Vaux1HwHPReq2Valid       = disabled
	 * Vaux2HwHPReq2Valid       = disabled
	 * Vaux3HwHPReq2Valid       = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUHWHPREQ2VALID1,     0xe8, 0x00),
	/*
	 * VextSupply1HwHPReq2Valid = disabled
	 * VextSupply2HwHPReq2Valid = disabled
	 * VextSupply3HwHPReq2Valid = HWReq2 controlled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUHWHPREQ2VALID2,     0x07, 0x04),
	/*
	 * VanaSwHPReqValid         = disabled
	 * Vaux1SwHPReqValid        = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUSWHPREQVALID1,      0xa0, 0x00),
	/*
	 * Vaux2SwHPReqValid        = disabled
	 * Vaux3SwHPReqValid        = disabled
	 * VextSupply1SwHPReqValid  = disabled
	 * VextSupply2SwHPReqValid  = disabled
	 * VextSupply3SwHPReqValid  = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUSWHPREQVALID2,      0x1f, 0x00),
	/*
	 * SysClkReq2Valid1         = SysClkReq2 controlled
	 * SysClkReq3Valid1         = disabled
	 * SysClkReq4Valid1         = SysClkReq4 controlled
	 * SysClkReq5Valid1         = disabled
	 * SysClkReq6Valid1         = SysClkReq6 controlled
	 * SysClkReq7Valid1         = disabled
	 * SysClkReq8Valid1         = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUSYSCLKREQVALID1,    0xfe, 0x2a),
	/*
	 * SysClkReq2Valid2         = disabled
	 * SysClkReq3Valid2         = disabled
	 * SysClkReq4Valid2         = disabled
	 * SysClkReq5Valid2         = disabled
	 * SysClkReq6Valid2         = SysClkReq6 controlled
	 * SysClkReq7Valid2         = disabled
	 * SysClkReq8Valid2         = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUSYSCLKREQVALID2,    0xfe, 0x20),
	/*
	 * VTVoutEna                = disabled
	 * Vintcore12Ena            = disabled
	 * Vintcore12Sel            = 1.25 V
	 * Vintcore12LP             = inactive (HP)
	 * VTVoutLP                 = inactive (HP)
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUMISC1,              0xfe, 0x10),
	/*
	 * VaudioEna                = disabled
	 * VdmicEna                 = disabled
	 * Vamic1Ena                = disabled
	 * Vamic2Ena                = disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_VAUDIOSUPPLY,           0x1e, 0x00),
	/*
	 * Vamic1_dzout             = high-Z when Vamic1 is disabled
	 * Vamic2_dzout             = high-Z when Vamic2 is disabled
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUCTRL1VAMIC,         0x03, 0x00),
	/*
	 * Vsmps1Regu               = HW control
	 * Vsmps1SelCtrl            = Vsmps1 voltage defined by Vsmsp1Sel2
	 */
	INIT_REGULATOR_REGISTER(AB8500_VSMPS1REGU,             0x0f, 0x06),
	/*
	 * Vsmps2Regu               = HW control
	 * Vsmps2SelCtrl            = Vsmps2 voltage defined by Vsmsp2Sel2
	 */
	INIT_REGULATOR_REGISTER(AB8500_VSMPS2REGU,             0x0f, 0x06),
	/*
	 * Vsmps3Sel2               = 1.2125 V
	 * NOTE! PRCMU register
	 */
	INIT_REGULATOR_REGISTER(AB8500_VSMPS3SEL2,             0x7f, 0x29),
	/*
	 * Vsmps3Regu               = HW control
	 * Vsmps3SelCtrl            = Vsmps3 voltage defined by Vsmps3Sel2
	 * NOTE! PRCMU register
	 */
	INIT_REGULATOR_REGISTER(AB8500_VSMPS3REGU,             0x0f, 0x06),
	/*
	 * Vsmps3Sel1               = 0.925V
	 * NOTE! PRCMU register
	 */
	INIT_REGULATOR_REGISTER(AB8500_VSMPS3SEL1,             0x7f, 0x12),
	/*
	 * VPll                     = Hw controlled
	 * VanaRegu                 = force off
	 */
	INIT_REGULATOR_REGISTER(AB8500_VPLLVANAREGU,           0x0f, 0x02),
	/*
	 * VrefDDREna               = disabled
	 * VrefDDRSleepMode         = inactive (no pulldown)
	 */
	INIT_REGULATOR_REGISTER(AB8500_VREFDDR,                0x03, 0x00),
	/*
	 * VextSupply1Regu          = HW control
	 * VextSupply2Regu          = HW control
	 * VextSupply3Regu          = Low Power mode
	 * ExtSupply2Bypass         = ExtSupply12LPn ball is 0 when Ena is 0
	 * ExtSupply3Bypass         = ExtSupply3LPn ball is 0 when Ena is 0
	 */
	INIT_REGULATOR_REGISTER(AB8500_EXTSUPPLYREGU,          0xff, 0x1a),
	/*
	 * Vaux1Regu                = force HP
	 * Vaux2Regu                = force off
	 */
	INIT_REGULATOR_REGISTER(AB8500_VAUX12REGU,             0x0f, 0x01),
	/*
	 * Vrf1Regu                 = HW control
	 * Vaux3Regu                = force off
	 */
	INIT_REGULATOR_REGISTER(AB8500_VRF1VAUX3REGU,          0x0f, 0x08),
	/*
	 * Vsmps1Sel1               = 1.2 V
	 */
	INIT_REGULATOR_REGISTER(AB8500_VSMPS1SEL1,             0x3f, 0x28),
	/*
	 * Vaux1Sel                 = 2.8 V
	 */
	INIT_REGULATOR_REGISTER(AB8500_VAUX1SEL,               0x0f, 0x0C),
	/*
	 * Vaux2Sel                 = 2.9 V
	 */
	INIT_REGULATOR_REGISTER(AB8500_VAUX2SEL,               0x0f, 0x0d),
	/*
	 * Vaux3Sel                 = 2.91 V
	 */
	INIT_REGULATOR_REGISTER(AB8500_VRF1VAUX3SEL,           0x07, 0x07),
	/*
	 * VextSupply12LP           = disabled (no LP)
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUCTRL2SPARE,         0x01, 0x00),
	/*
	 * Vaux1Disch               = short discharge time
	 * Vaux2Disch               = short discharge time
	 * Vaux3Disch               = short discharge time
	 * Vintcore12Disch          = short discharge time
	 * VTVoutDisch              = short discharge time
	 * VaudioDisch              = short discharge time
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUCTRLDISCH,          0xfc, 0x00),
	/*
	 * VanaDisch                = short discharge time
	 * VdmicPullDownEna         = pulldown disabled when Vdmic is disabled
	 * VdmicDisch               = short discharge time
	 */
	INIT_REGULATOR_REGISTER(AB8500_REGUCTRLDISCH2,         0x16, 0x00),
};

/* AB8500 regulators */
static struct regulator_init_data ab8500_regulators[AB8500_NUM_REGULATORS] = {
	/* supplies to the display/camera */
	[AB8500_LDO_AUX1] = {
		.supply_regulator = "ab8500-ext-supply3",
		.constraints = {
			.name = "V-DISPLAY",
			.min_uV = 2800000,
			.max_uV = 3300000,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
					  REGULATOR_CHANGE_STATUS,
			.boot_on = 1, /* display is on at boot */
			/*
			 * This voltage cannot be disabled right now because
			 * it is somehow affecting the external MMC
			 * functionality, though that typically will use
			 * AUX3.
			 */
			.always_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vaux1_consumers),
		.consumer_supplies = ab8500_vaux1_consumers,
	},
	/* supplies to the on-board eMMC */
	[AB8500_LDO_AUX2] = {
		.supply_regulator = "ab8500-ext-supply3",
		.constraints = {
			.name = "V-eMMC1",
			.min_uV = 1100000,
			.max_uV = 3300000,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
					  REGULATOR_CHANGE_STATUS |
					  REGULATOR_CHANGE_MODE,
			.valid_modes_mask = REGULATOR_MODE_NORMAL |
					    REGULATOR_MODE_IDLE,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vaux2_consumers),
		.consumer_supplies = ab8500_vaux2_consumers,
	},
	/* supply for VAUX3, supplies to SDcard slots */
	[AB8500_LDO_AUX3] = {
		.supply_regulator = "ab8500-ext-supply3",
		.constraints = {
			.name = "V-MMC-SD",
			.min_uV = 1100000,
			.max_uV = 3300000,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
					  REGULATOR_CHANGE_STATUS |
					  REGULATOR_CHANGE_MODE,
			.valid_modes_mask = REGULATOR_MODE_NORMAL |
					    REGULATOR_MODE_IDLE,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vaux3_consumers),
		.consumer_supplies = ab8500_vaux3_consumers,
	},
	/* supply for tvout, gpadc, TVOUT LDO */
	[AB8500_LDO_TVOUT] = {
		.constraints = {
			.name = "V-TVOUT",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vtvout_consumers),
		.consumer_supplies = ab8500_vtvout_consumers,
	},
	/* supply for ab8500-vaudio, VAUDIO LDO */
	[AB8500_LDO_AUDIO] = {
		.constraints = {
			.name = "V-AUD",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vaudio_consumers),
		.consumer_supplies = ab8500_vaudio_consumers,
	},
	/* supply for v-anamic1 VAMic1-LDO */
	[AB8500_LDO_ANAMIC1] = {
		.constraints = {
			.name = "V-AMIC1",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vamic1_consumers),
		.consumer_supplies = ab8500_vamic1_consumers,
	},
	/* supply for v-amic2, VAMIC2 LDO, reuse constants for AMIC1 */
	[AB8500_LDO_ANAMIC2] = {
		.constraints = {
			.name = "V-AMIC2",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vamic2_consumers),
		.consumer_supplies = ab8500_vamic2_consumers,
	},
	/* supply for v-dmic, VDMIC LDO */
	[AB8500_LDO_DMIC] = {
		.constraints = {
			.name = "V-DMIC",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vdmic_consumers),
		.consumer_supplies = ab8500_vdmic_consumers,
	},
	/* supply for v-intcore12, VINTCORE12 LDO */
	[AB8500_LDO_INTCORE] = {
		.constraints = {
			.name = "V-INTCORE",
			.min_uV = 1250000,
			.max_uV = 1350000,
			.input_uV = 1800000,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
					  REGULATOR_CHANGE_STATUS |
					  REGULATOR_CHANGE_MODE |
					  REGULATOR_CHANGE_DRMS,
			.valid_modes_mask = REGULATOR_MODE_NORMAL |
					    REGULATOR_MODE_IDLE,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vintcore_consumers),
		.consumer_supplies = ab8500_vintcore_consumers,
	},
	/* supply for U8500 CSI-DSI, VANA LDO */
	[AB8500_LDO_ANA] = {
		.constraints = {
			.name = "V-CSI-DSI",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(ab8500_vana_consumers),
		.consumer_supplies = ab8500_vana_consumers,
	},
	/* sysclkreq 2 pin */
	[AB8500_SYSCLKREQ_2] = {
		.constraints = {
			.name = "V-SYSCLKREQ-2",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies =
			ARRAY_SIZE(ab8500_sysclkreq_2_consumers),
		.consumer_supplies = ab8500_sysclkreq_2_consumers,
	},
	/* sysclkreq 4 pin */
	[AB8500_SYSCLKREQ_4] = {
		.constraints = {
			.name = "V-SYSCLKREQ-4",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies =
			ARRAY_SIZE(ab8500_sysclkreq_4_consumers),
		.consumer_supplies = ab8500_sysclkreq_4_consumers,
	},
};

/* supply for VextSupply3 */
static struct regulator_consumer_supply ab8500_ext_supply3_consumers[] = {
	/* SIM supply for 3 V SIM cards */
	REGULATOR_SUPPLY("vinvsim", "sim-detect.0"),
};

/*
 * AB8500 external regulators
 */
static struct regulator_init_data ab8500_ext_regulators[] = {
	/* fixed Vbat supplies VSMPS3_EXT_3V4 and VSMPS4_EXT_3V4 */
	[AB8500_EXT_SUPPLY3] = {
		.constraints = {
			.name = "ab8500-ext-supply3",
			.min_uV = 3400000,
			.max_uV = 3400000,
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
			.boot_on = 1,
		},
		.num_consumer_supplies =
			ARRAY_SIZE(ab8500_ext_supply3_consumers),
		.consumer_supplies = ab8500_ext_supply3_consumers,
	},
};

struct ab8500_regulator_platform_data ab8500_regulator_plat_data = {
	.reg_init               = ab8500_reg_init,
	.num_reg_init           = ARRAY_SIZE(ab8500_reg_init),
	.regulator              = ab8500_regulators,
	.num_regulator          = ARRAY_SIZE(ab8500_regulators),
	.ext_regulator          = ab8500_ext_regulators,
	.num_ext_regulator      = ARRAY_SIZE(ab8500_ext_regulators),
};
