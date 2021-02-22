EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3550 2600 3350 2600
Wire Wire Line
	3350 3600 3550 3600
Wire Wire Line
	3550 3500 3350 3500
Connection ~ 3350 3500
Wire Wire Line
	3350 3500 3350 3600
Wire Wire Line
	3550 3400 3350 3400
Connection ~ 3350 3400
Wire Wire Line
	3350 3400 3350 3500
Wire Wire Line
	3550 3300 3350 3300
Connection ~ 3350 3300
Wire Wire Line
	3350 3300 3350 3400
Wire Wire Line
	3550 3200 3350 3200
Connection ~ 3350 3200
Wire Wire Line
	3350 3200 3350 3300
Wire Wire Line
	3550 3100 3350 3100
Connection ~ 3350 3100
Wire Wire Line
	3350 3100 3350 3200
Wire Wire Line
	3550 3000 3350 3000
Wire Wire Line
	3350 2600 3350 2700
Connection ~ 3350 3000
Wire Wire Line
	3350 3000 3350 3100
Wire Wire Line
	3550 2900 3350 2900
Connection ~ 3350 2900
Wire Wire Line
	3350 2900 3350 3000
Wire Wire Line
	3550 2800 3350 2800
Connection ~ 3350 2800
Wire Wire Line
	3350 2800 3350 2900
Wire Wire Line
	3550 2700 3350 2700
Connection ~ 3350 2700
Wire Wire Line
	3350 2700 3350 2800
Wire Wire Line
	3550 2450 3350 2450
Wire Wire Line
	3350 2450 3350 2350
Wire Wire Line
	3550 2350 3350 2350
Connection ~ 3350 2350
Wire Wire Line
	3350 2350 3350 2250
Wire Wire Line
	3350 2700 3250 2700
Wire Wire Line
	3250 2700 3250 1650
$Comp
L Device:C C4
U 1 1 5EBD35B2
P 2750 3750
F 0 "C4" V 2498 3750 50  0000 C CNN
F 1 "10 n" V 2589 3750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2788 3600 50  0001 C CNN
F 3 "~" H 2750 3750 50  0001 C CNN
	1    2750 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 3750 3550 3750
$Comp
L Device:R R1
U 1 1 5EBD35BB
P 2450 3850
F 0 "R1" V 2243 3850 50  0000 C CNN
F 1 "22 k" V 2334 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2380 3850 50  0001 C CNN
F 3 "~" H 2450 3850 50  0001 C CNN
	1    2450 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 3850 2600 3850
$Comp
L Device:C C5
U 1 1 5EBD35D0
P 2900 2000
F 0 "C5" H 3015 2046 50  0000 L CNN
F 1 "33 p" H 3015 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2938 1850 50  0001 C CNN
F 3 "~" H 2900 2000 50  0001 C CNN
	1    2900 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5EBD35D6
P 2450 2000
F 0 "C1" H 2565 2046 50  0000 L CNN
F 1 "4.7 n" H 2565 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2488 1850 50  0001 C CNN
F 3 "~" H 2450 2000 50  0001 C CNN
	1    2450 2000
	1    0    0    -1  
$EndComp
Connection ~ 3250 1650
$Comp
L Device:L L2
U 1 1 5EBD35F3
P 6500 2200
F 0 "L2" V 6690 2200 50  0000 C CNN
F 1 "39 n" V 6599 2200 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6500 2200 50  0001 C CNN
F 3 "~" H 6500 2200 50  0001 C CNN
	1    6500 2200
	0    -1   -1   0   
$EndComp
$Comp
L Device:L L3
U 1 1 5EBD35F9
P 6550 2500
F 0 "L3" V 6369 2500 50  0000 C CNN
F 1 "39 n" V 6460 2500 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6550 2500 50  0001 C CNN
F 3 "~" H 6550 2500 50  0001 C CNN
	1    6550 2500
	0    1    1    0   
$EndComp
$Comp
L Device:L L1
U 1 1 5EBD35FF
P 6050 2350
F 0 "L1" H 6102 2396 50  0000 L CNN
F 1 "12 n" H 6102 2305 50  0000 L CNN
F 2 "Inductor_SMD:L_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6050 2350 50  0001 C CNN
F 3 "~" H 6050 2350 50  0001 C CNN
	1    6050 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2250 5150 2250
Wire Wire Line
	5800 2250 5800 2200
Wire Wire Line
	5800 2350 5800 2500
$Comp
L Device:C C11
U 1 1 5EBD3611
P 7050 3000
F 0 "C11" V 6798 3000 50  0000 C CNN
F 1 "3.3 n" V 6889 3000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7088 2850 50  0001 C CNN
F 3 "~" H 7050 3000 50  0001 C CNN
	1    7050 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5050 2450 5750 2450
$Comp
L Device:C C10
U 1 1 5EBD3622
P 7050 2500
F 0 "C10" V 7250 2500 50  0000 C CNN
F 1 "180 p" V 7350 2500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7088 2350 50  0001 C CNN
F 3 "~" H 7050 2500 50  0001 C CNN
	1    7050 2500
	0    1    1    0   
$EndComp
$Comp
L Device:C C8
U 1 1 5EBD362D
P 5550 1950
F 0 "C8" H 5665 1996 50  0000 L CNN
F 1 "18 p" H 5665 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5588 1800 50  0001 C CNN
F 3 "~" H 5550 1950 50  0001 C CNN
	1    5550 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5EBD3633
P 5150 1950
F 0 "C7" H 5265 1996 50  0000 L CNN
F 1 "18 p" H 5265 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5188 1800 50  0001 C CNN
F 3 "~" H 5150 1950 50  0001 C CNN
	1    5150 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial J1
U 1 1 5EBD363F
P 7500 2200
F 0 "J1" H 7600 2175 50  0000 L CNN
F 1 "Conn_Coaxial" H 7600 2084 50  0000 L CNN
F 2 "Connector_Coaxial:U.FL_Molex_MCRF_73412-0110_Vertical" H 7500 2200 50  0001 C CNN
F 3 " ~" H 7500 2200 50  0001 C CNN
	1    7500 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1850 2450 1650
Wire Wire Line
	2450 2150 2450 2350
$Comp
L power:GND #PWR0101
U 1 1 5EBED4BE
P 7500 3050
F 0 "#PWR0101" H 7500 2800 50  0001 C CNN
F 1 "GND" H 7505 2877 50  0000 C CNN
F 2 "" H 7500 3050 50  0001 C CNN
F 3 "" H 7500 3050 50  0001 C CNN
	1    7500 3050
	1    0    0    -1  
$EndComp
Connection ~ 3250 2700
Connection ~ 2450 2350
Text HLabel 5050 3050 2    50   Output ~ 0
NRF_MISO
Text HLabel 5050 2950 2    50   Input ~ 0
NRF_MOSI
Text HLabel 5050 3150 2    50   Input ~ 0
NRF_CLK
Text HLabel 5050 3250 2    50   Input ~ 0
CS_NRF
Text HLabel 5050 3400 2    50   Input ~ 0
NRF_CE
Text HLabel 5050 3500 2    50   Input ~ 0
NRF_PWR
Text HLabel 5050 3600 2    50   Input ~ 0
NRF_TX_EN
Text HLabel 5050 3750 2    50   Output ~ 0
NRF_CD
Text HLabel 5050 3850 2    50   Output ~ 0
NRF_AM
Text HLabel 5050 3950 2    50   Output ~ 0
NRF_DR
Text HLabel 2600 2700 0    50   UnSpc ~ 0
GND
Wire Wire Line
	2000 2350 2450 2350
Wire Wire Line
	2600 2700 3050 2700
$Comp
L RECIVER_NRF-rescue:NRF905-_wireless U1
U 1 1 5EBD3534
P 4300 3200
F 0 "U1" H 4300 4437 60  0000 C CNN
F 1 "NRF905" H 4300 4331 60  0000 C CNN
F 2 "Package_DFN_QFN:QFN-32-1EP_5x5mm_P0.5mm_EP3.6x3.6mm" H 4300 3150 60  0001 C CNN
F 3 "" H 4300 3150 60  0000 C CNN
	1    4300 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5EBD35C5
P 3500 2000
F 0 "C6" H 3615 2046 50  0000 L CNN
F 1 "33 p" H 3615 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3538 1850 50  0001 C CNN
F 3 "~" H 3500 2000 50  0001 C CNN
	1    3500 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 3950 3550 4000
Wire Wire Line
	3550 4250 3550 4100
$Comp
L Device:C C2
U 1 1 5EB90A98
P 2500 4200
F 0 "C2" V 2248 4200 50  0000 C CNN
F 1 "22 p" V 2339 4200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2538 4050 50  0001 C CNN
F 3 "~" H 2500 4200 50  0001 C CNN
	1    2500 4200
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 5EB917BB
P 2500 4600
F 0 "C3" V 2248 4600 50  0000 C CNN
F 1 "22 p" V 2339 4600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2538 4450 50  0001 C CNN
F 3 "~" H 2500 4600 50  0001 C CNN
	1    2500 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 4200 2650 3950
Wire Wire Line
	2650 3950 2750 3950
Wire Wire Line
	2650 4600 2750 4600
Wire Wire Line
	3000 4600 3000 4250
Wire Wire Line
	2350 4200 2150 4200
Wire Wire Line
	2150 4200 2150 4600
Wire Wire Line
	2150 4600 2350 4600
Connection ~ 2150 4200
$Comp
L Device:R R2
U 1 1 5EB9E4FF
P 2750 4350
F 0 "R2" H 2820 4396 50  0000 L CNN
F 1 "1 M" H 2820 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2680 4350 50  0001 C CNN
F 3 "~" H 2750 4350 50  0001 C CNN
	1    2750 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 4200 2750 3950
Connection ~ 2750 3950
Wire Wire Line
	2750 4500 2750 4600
Connection ~ 2750 4600
Wire Wire Line
	2750 4600 3000 4600
$Comp
L power:GND #PWR0102
U 1 1 5EBEDA90
P 3050 2900
F 0 "#PWR0102" H 3050 2650 50  0001 C CNN
F 1 "GND" H 3055 2727 50  0000 C CNN
F 2 "" H 3050 2900 50  0001 C CNN
F 3 "" H 3050 2900 50  0001 C CNN
	1    3050 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 1650 3500 1650
Wire Wire Line
	3500 1850 3500 1650
Wire Wire Line
	3350 2250 3500 2250
Connection ~ 3500 1650
Wire Wire Line
	3500 1650 5150 1650
Wire Wire Line
	3500 2150 3500 2250
Connection ~ 3500 2250
Wire Wire Line
	3500 2250 3550 2250
Wire Wire Line
	2450 2350 2900 2350
Wire Wire Line
	2450 1650 2900 1650
Wire Wire Line
	2900 2150 2900 2350
Connection ~ 2900 2350
Wire Wire Line
	2900 2350 3350 2350
Wire Wire Line
	2900 1850 2900 1650
Connection ~ 2900 1650
Wire Wire Line
	2900 1650 3250 1650
Wire Wire Line
	3050 2900 3050 2700
Connection ~ 3050 2700
Wire Wire Line
	3050 2700 3250 2700
Wire Wire Line
	3350 3200 2600 3200
Wire Wire Line
	2150 3200 2150 4200
Wire Wire Line
	2300 3200 2300 3850
Connection ~ 2300 3200
Wire Wire Line
	2300 3200 2150 3200
Wire Wire Line
	2600 3200 2600 3750
Connection ~ 2600 3200
Wire Wire Line
	2600 3200 2300 3200
Wire Wire Line
	2750 3950 3200 3950
Wire Wire Line
	3000 4250 3200 4250
$Comp
L Device:Crystal Y1
U 1 1 5EB6F079
P 3200 4100
F 0 "Y1" V 3154 4231 50  0000 L CNN
F 1 "Crystal" V 3245 4231 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_TXC_7A-2Pin_5x3.2mm" H 3200 4100 50  0001 C CNN
F 3 "~" H 3200 4100 50  0001 C CNN
	1    3200 4100
	0    1    1    0   
$EndComp
Connection ~ 3200 3950
Wire Wire Line
	3200 3950 3550 3950
Connection ~ 3200 4250
Wire Wire Line
	3200 4250 3550 4250
Wire Wire Line
	5750 2450 5750 3000
Wire Wire Line
	5750 3000 6800 3000
Wire Wire Line
	6800 2500 6800 3000
Wire Wire Line
	5800 2500 6050 2500
Connection ~ 6050 2200
Wire Wire Line
	6050 2200 6350 2200
Connection ~ 6050 2500
Wire Wire Line
	6050 2500 6400 2500
Wire Wire Line
	6700 2500 6800 2500
Connection ~ 6800 2500
Wire Wire Line
	6800 2500 6900 2500
Connection ~ 6800 3000
Wire Wire Line
	6800 3000 6900 3000
$Comp
L Device:C C9
U 1 1 5EBD361C
P 7050 2200
F 0 "C9" V 6798 2200 50  0000 C CNN
F 1 "6.8 p" V 6889 2200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7088 2050 50  0001 C CNN
F 3 "~" H 7050 2200 50  0001 C CNN
	1    7050 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 2200 6900 2200
Wire Wire Line
	7200 2200 7300 2200
Wire Wire Line
	7200 2500 7500 2500
Wire Wire Line
	7500 2500 7500 2400
Wire Wire Line
	7200 3000 7500 3000
Wire Wire Line
	7500 3000 7500 3050
Wire Wire Line
	7500 3000 7500 2500
Connection ~ 7500 3000
Connection ~ 7500 2500
Wire Wire Line
	5150 1800 5150 1650
Connection ~ 5150 1650
Wire Wire Line
	5150 2100 5150 2250
Connection ~ 5150 2250
Wire Wire Line
	5150 2250 5800 2250
Wire Wire Line
	5050 2350 5550 2350
Wire Wire Line
	5150 1650 5550 1650
Wire Wire Line
	5550 1800 5550 1650
Wire Wire Line
	5550 2100 5550 2350
Connection ~ 5550 2350
Wire Wire Line
	5550 2350 5800 2350
Wire Wire Line
	5800 2200 6050 2200
NoConn ~ 5050 4100
Text HLabel 2000 2350 0    50   Input ~ 0
VDD_NRF
$EndSCHEMATC
