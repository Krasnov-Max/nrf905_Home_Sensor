EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
	5750 3100 5750 3050
Wire Wire Line
	5950 3050 5750 3050
Wire Wire Line
	5950 3100 5950 3050
Wire Wire Line
	5950 4300 5750 4300
$Comp
L Sensor:BME280 U2
U 1 1 5EBFE082
P 5850 3700
F 0 "U2" H 5421 3746 50  0000 R CNN
F 1 "BME280" H 5550 4200 50  0000 R CNN
F 2 "Package_LGA:Bosch_LGA-8_2.5x2.5mm_P0.65mm_ClockwisePinNumbering" H 7350 3250 50  0001 C CNN
F 3 "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf" H 5850 3500 50  0001 C CNN
	1    5850 3700
	1    0    0    -1  
$EndComp
Text HLabel 6550 4000 2    50   Input ~ 0
CS_BME
Text HLabel 6550 3400 2    50   Output ~ 0
MISO
Text HLabel 6550 3600 2    50   Input ~ 0
CSK
Text HLabel 6550 3800 2    50   Input ~ 0
MOSI
Wire Wire Line
	6450 3400 6550 3400
Wire Wire Line
	6450 3600 6550 3600
Wire Wire Line
	6450 3800 6550 3800
Wire Wire Line
	6450 4000 6550 4000
$Comp
L Device:C C5
U 1 1 5EC489DE
P 4850 3700
F 0 "C5" H 4965 3746 50  0000 L CNN
F 1 "4.7 uf" H 4965 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4888 3550 50  0001 C CNN
F 3 "~" H 4850 3700 50  0001 C CNN
	1    4850 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5EC48C40
P 4550 3700
F 0 "C4" H 4350 3800 50  0000 L CNN
F 1 "0.1 uf" H 4300 3600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4588 3550 50  0001 C CNN
F 3 "~" H 4550 3700 50  0001 C CNN
	1    4550 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4300 4850 4300
Wire Wire Line
	4550 4300 4550 3850
Connection ~ 5750 4300
Wire Wire Line
	4850 3850 4850 4300
Connection ~ 4850 4300
Wire Wire Line
	4850 4300 4550 4300
Wire Wire Line
	4550 3550 4550 3050
Wire Wire Line
	4550 3050 4850 3050
Connection ~ 5750 3050
Wire Wire Line
	4850 3550 4850 3050
Connection ~ 4850 3050
Wire Wire Line
	4850 3050 5750 3050
Text HLabel 4350 3050 0    50   UnSpc ~ 0
VDD_P
Text HLabel 4250 4300 0    50   UnSpc ~ 0
GND
Wire Wire Line
	4250 4300 4550 4300
Connection ~ 4550 4300
Wire Wire Line
	4350 3050 4550 3050
Connection ~ 4550 3050
$EndSCHEMATC
