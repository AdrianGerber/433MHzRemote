/*
 * 433MHz_SW.c
 *
 * Created: 02.07.2016
 *  Author: Adrian Gerber
 */ 

 #include "433MHz_SW.h"


 void SW_Setup(void){
	 /*Set GPIO Pin as output*/
	 SW_GPIO_DDR |= (1<<SW_GPIO_BIT);
	 /*Make sure it's LOW*/
	 SW_GPIO_LOW;
	 /*Mark all tasks as done*/
	 for(uint8_t i = 0; i < SW_TASKCOUNT; i++) SW_tasks[i].refresh = 0;
 }

 /*Generates signal:*/
 /* ___ 1  */
 /*| 3 |_ */
 void SW_SendBit1(void){
	 SW_GPIO_HIGH;
	 _delay_us(SW_PULSE_LENGTH_US*3);
	 SW_GPIO_LOW;
	 _delay_us(SW_PULSE_LENGTH_US);
 }

 /*Generates signal:*/
 /* _  3  */
 /*|1|___ */
 void SW_SendBit0(void){
	 SW_GPIO_HIGH;
	 _delay_us(SW_PULSE_LENGTH_US);
	 SW_GPIO_LOW;
	 _delay_us(SW_PULSE_LENGTH_US*3);
 }

 /*Generates signal:			   	 */
 /* _				31  			 */
 /*|1|_______________________________*/
 void SW_SendSync(void){
	 SW_GPIO_HIGH;
	 _delay_us(SW_PULSE_LENGTH_US);
	 SW_GPIO_LOW;
	 _delay_us(SW_PULSE_LENGTH_US*31);
 }

 /*Generates signal:*/
 /* _  3  _  3 */
 /*|1|___|1|___*/
 void SW_Send0(void){
	 SW_SendBit0();
	 SW_SendBit0();
 }

 /*Generates signal:*/
 /* ___ 1 ___ 1*/
 /*| 3 |_| 3 |_*/
 void SW_Send1(void){
	 SW_SendBit1();
	 SW_SendBit1();
 }

 /*Generates signal:*/
 /* _  3  ___ 1 */
 /*|1|___| 3 |_ */
 void SW_SendF(void){
	 SW_SendBit0();
	 SW_SendBit1();
 }

 /*Send a string of "TRI"- Characters*/
 void SW_SendTRI(char *str){
	 /*Loop until '\0' is found*/
	 while(*str){
		 /*Chose which character to send*/
		 switch(*str){
			 case '0': SW_Send0();    break;
			 case '1': SW_Send1();    break;
			 case 'F': SW_SendF();	 break;
			 case 'S': SW_SendSync(); break;
			 default : 				 break;
		 }

		 /*Go to the next character of the string*/
		 str++;
	 }
 }

 /*Send a string of "TRI"- Characters*/
 void SW_SendTRIRepeat(char *str, uint8_t repeadCnt){
	 /*Send str multiple times*/
	 while(repeadCnt-- > 0){
		 SW_SendTRI(str);
	 }
 }

 /*Set the state of a remote switch*/
 void SW_SetSwitch(uint8_t addr, uint8_t channel, uint8_t repeatCnt, uint8_t state){
	 char triCode[sizeof(SW_SWITCHSTRING)];
	 
	 /*Change addr and channel to start counting at 0*/
	 addr--;
	 channel--;

	 /*Mask out all unused bits*/
	 addr    &= 0x03;
	 channel &= 0x03;

	 /*Fill array with 'F', add '\0' to the end*/
	 for(uint8_t i = 0; i < sizeof(SW_SWITCHSTRING); i++) triCode[i] = 'F';
	 triCode[sizeof(SW_SWITCHSTRING)-1] = '\0';

	 /*Select address and channel*/
	 triCode[addr] = '0';
	 triCode[4+channel] = '0';
	 
	 /*Add Sync character*/
	 triCode[sizeof(SW_SWITCHSTRING)-2] = 'S';
	 /*Change state to 0 if needed*/
	 if(!state) triCode[sizeof(SW_SWITCHSTRING)-3] = '0';

	 SW_SendTRIRepeat(triCode, repeatCnt);
 }
