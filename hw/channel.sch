EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:RJ45_Shielded JIN1
U 1 1 5D68EF89
P 3100 3900
AR Path="/5D68E8B9/5D68EF89" Ref="JIN1"  Part="1" 
AR Path="/5D6AB3A6/5D68EF89" Ref="JIN?"  Part="1" 
AR Path="/5D6AC3EB/5D68EF89" Ref="JIN?"  Part="1" 
AR Path="/5D6AC3F5/5D68EF89" Ref="JIN?"  Part="1" 
AR Path="/5D713368/5D68EF89" Ref="JIN?"  Part="1" 
AR Path="/5DB48D9F/5D68EF89" Ref="JIN2"  Part="1" 
AR Path="/5DB6E72C/5D68EF89" Ref="JIN3"  Part="1" 
AR Path="/5DB6E750/5D68EF89" Ref="JIN4"  Part="1" 
F 0 "JIN4" H 3100 4550 50  0000 C CNN
F 1 "6339160-1" H 3100 4450 50  0000 C CNN
F 2 "rj45-6339160-1:6339160-1" V 3100 3925 50  0001 C CNN
F 3 "~" V 3100 3925 50  0001 C CNN
	1    3100 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4100 3800 4100
Wire Wire Line
	3800 4200 3500 4200
Text Label 3800 4200 2    50   ~ 0
CH0_P
$Comp
L Relay:G6KU-2 K4
U 1 1 5D697648
P 5150 6000
AR Path="/5D68E8B9/5D697648" Ref="K4"  Part="1" 
AR Path="/5D6AB3A6/5D697648" Ref="K?"  Part="1" 
AR Path="/5D6AC3EB/5D697648" Ref="K?"  Part="1" 
AR Path="/5D6AC3F5/5D697648" Ref="K?"  Part="1" 
AR Path="/5D713368/5D697648" Ref="K?"  Part="1" 
AR Path="/5DB48D9F/5D697648" Ref="K8"  Part="1" 
AR Path="/5DB6E72C/5D697648" Ref="K12"  Part="1" 
AR Path="/5DB6E750/5D697648" Ref="K16"  Part="1" 
F 0 "K16" V 4383 6000 50  0000 C CNN
F 1 "G6KU-2" V 4474 6000 50  0000 C CNN
F 2 "Relay_SMD:Relay_DPDT_Omron_G6K-2F-Y" H 5800 5950 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6k.pdf" H 4950 6000 50  0001 C CNN
	1    5150 6000
	0    -1   1    0   
$EndComp
Text HLabel 5450 5600 2    50   Input ~ 0
SW_COM
Text HLabel 5450 6400 2    50   Input ~ 0
COM_P
Text HLabel 5450 6000 2    50   Input ~ 0
COM_N
Text HLabel 4850 5600 0    50   Input ~ 0
SW0
Text HLabel 3100 4400 3    50   Input ~ 0
GND
NoConn ~ 4850 5900
NoConn ~ 4850 6300
Wire Wire Line
	4850 6100 4550 6100
Wire Wire Line
	4550 6500 4850 6500
Text Label 3800 4100 2    50   ~ 0
CH0_N
Wire Wire Line
	3500 3900 3800 3900
Wire Wire Line
	3800 4000 3500 4000
Text Label 3800 4000 2    50   ~ 0
CH1_P
Text Label 3800 3900 2    50   ~ 0
CH1_N
Wire Wire Line
	3500 3700 3800 3700
Wire Wire Line
	3800 3800 3500 3800
Text Label 3800 3800 2    50   ~ 0
CH2_P
Text Label 3800 3700 2    50   ~ 0
CH2_N
Wire Wire Line
	3500 3500 3800 3500
Wire Wire Line
	3800 3600 3500 3600
Text Label 3800 3600 2    50   ~ 0
CH3_P
Text Label 3800 3500 2    50   ~ 0
CH3_N
Text Label 4550 6500 0    50   ~ 0
CH0_P
Text Label 4550 6100 0    50   ~ 0
CH0_N
$Comp
L Relay:G6KU-2 K3
U 1 1 5DB2F3C7
P 5150 4550
AR Path="/5D68E8B9/5DB2F3C7" Ref="K3"  Part="1" 
AR Path="/5D6AB3A6/5DB2F3C7" Ref="K?"  Part="1" 
AR Path="/5D6AC3EB/5DB2F3C7" Ref="K?"  Part="1" 
AR Path="/5D6AC3F5/5DB2F3C7" Ref="K?"  Part="1" 
AR Path="/5D713368/5DB2F3C7" Ref="K?"  Part="1" 
AR Path="/5DB48D9F/5DB2F3C7" Ref="K7"  Part="1" 
AR Path="/5DB6E72C/5DB2F3C7" Ref="K11"  Part="1" 
AR Path="/5DB6E750/5DB2F3C7" Ref="K15"  Part="1" 
F 0 "K15" V 4383 4550 50  0000 C CNN
F 1 "G6KU-2" V 4474 4550 50  0000 C CNN
F 2 "Relay_SMD:Relay_DPDT_Omron_G6K-2F-Y" H 5800 4500 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6k.pdf" H 4950 4550 50  0001 C CNN
	1    5150 4550
	0    -1   1    0   
$EndComp
Text HLabel 5450 4150 2    50   Input ~ 0
SW_COM
Text HLabel 5450 4950 2    50   Input ~ 0
COM_P
Text HLabel 5450 4550 2    50   Input ~ 0
COM_N
Text HLabel 4850 4150 0    50   Input ~ 0
SW1
NoConn ~ 4850 4450
NoConn ~ 4850 4850
Wire Wire Line
	4850 4650 4550 4650
Wire Wire Line
	4550 5050 4850 5050
Text Label 4550 5050 0    50   ~ 0
CH1_P
Text Label 4550 4650 0    50   ~ 0
CH1_N
$Comp
L Relay:G6KU-2 K2
U 1 1 5DB30ED1
P 5150 3100
AR Path="/5D68E8B9/5DB30ED1" Ref="K2"  Part="1" 
AR Path="/5D6AB3A6/5DB30ED1" Ref="K?"  Part="1" 
AR Path="/5D6AC3EB/5DB30ED1" Ref="K?"  Part="1" 
AR Path="/5D6AC3F5/5DB30ED1" Ref="K?"  Part="1" 
AR Path="/5D713368/5DB30ED1" Ref="K?"  Part="1" 
AR Path="/5DB48D9F/5DB30ED1" Ref="K6"  Part="1" 
AR Path="/5DB6E72C/5DB30ED1" Ref="K10"  Part="1" 
AR Path="/5DB6E750/5DB30ED1" Ref="K14"  Part="1" 
F 0 "K14" V 4383 3100 50  0000 C CNN
F 1 "G6KU-2" V 4474 3100 50  0000 C CNN
F 2 "Relay_SMD:Relay_DPDT_Omron_G6K-2F-Y" H 5800 3050 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6k.pdf" H 4950 3100 50  0001 C CNN
	1    5150 3100
	0    -1   1    0   
$EndComp
Text HLabel 5450 2700 2    50   Input ~ 0
SW_COM
Text HLabel 5450 3500 2    50   Input ~ 0
COM_P
Text HLabel 5450 3100 2    50   Input ~ 0
COM_N
Text HLabel 4850 2700 0    50   Input ~ 0
SW2
NoConn ~ 4850 3000
NoConn ~ 4850 3400
Wire Wire Line
	4850 3200 4550 3200
Wire Wire Line
	4550 3600 4850 3600
Text Label 4550 3600 0    50   ~ 0
CH2_P
Text Label 4550 3200 0    50   ~ 0
CH2_N
$Comp
L Relay:G6KU-2 K1
U 1 1 5DB30EE5
P 5150 1650
AR Path="/5D68E8B9/5DB30EE5" Ref="K1"  Part="1" 
AR Path="/5D6AB3A6/5DB30EE5" Ref="K?"  Part="1" 
AR Path="/5D6AC3EB/5DB30EE5" Ref="K?"  Part="1" 
AR Path="/5D6AC3F5/5DB30EE5" Ref="K?"  Part="1" 
AR Path="/5D713368/5DB30EE5" Ref="K?"  Part="1" 
AR Path="/5DB48D9F/5DB30EE5" Ref="K5"  Part="1" 
AR Path="/5DB6E72C/5DB30EE5" Ref="K9"  Part="1" 
AR Path="/5DB6E750/5DB30EE5" Ref="K13"  Part="1" 
F 0 "K13" V 4383 1650 50  0000 C CNN
F 1 "G6KU-2" V 4474 1650 50  0000 C CNN
F 2 "Relay_SMD:Relay_DPDT_Omron_G6K-2F-Y" H 5800 1600 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6k.pdf" H 4950 1650 50  0001 C CNN
	1    5150 1650
	0    -1   1    0   
$EndComp
Text HLabel 5450 1250 2    50   Input ~ 0
SW_COM
Text HLabel 5450 2050 2    50   Input ~ 0
COM_P
Text HLabel 5450 1650 2    50   Input ~ 0
COM_N
Text HLabel 4850 1250 0    50   Input ~ 0
SW3
NoConn ~ 4850 1550
NoConn ~ 4850 1950
Wire Wire Line
	4850 1750 4550 1750
Wire Wire Line
	4550 2150 4850 2150
Text Label 4550 2150 0    50   ~ 0
CH3_P
Text Label 4550 1750 0    50   ~ 0
CH3_N
$EndSCHEMATC
