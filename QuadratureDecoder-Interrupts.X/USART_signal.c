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
  line[i] = getchar();
  if (line[i] == '\n') break;
  i++;
}
line[i] = 0;
 * which would get each char line by line until \0 is reached 
 * further testing is required.
 */
uint8_t uart_getchar(void) {
  while ((UCSRA & (1 << RXC)) == 0) {
  }
  return UDR;
}