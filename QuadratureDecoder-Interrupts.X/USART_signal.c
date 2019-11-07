// Skeleton code file for USART of decoder signals

// basic form for method to send USART messages
// needs: input signals from the decoder
// returns: a data packet which can be send over USART to the user system
uint8_t sendDecoderSignals(){
	
}


/*
 Working on task 43 attempting to find a solution that works 
 
 * The current solution is based off research and has not yet been fully tested.
 * Ideally using this function then we could do something like - 
 * 
  while(1) {
  line[i] = usart_getchar();
  if (line[i] == '\n') break;
  i++;
}
line[i] = 0;
 * which would get each char line by line until \0 is reached 
 * further testing is required.
 */
unsigned char usart_getchar(void) {
  while ((UCSR0A & (1 << RXC)) == 0) {
  }
  return UDR0;
}

/*
 method stub for transmitting data in a char array over usart
 */
void USART0_Send(unsigned char data){
 
    
    while(!(UCSR0A & (1 << UDRE0)));
 
    
    UDR0 = data;
 
}