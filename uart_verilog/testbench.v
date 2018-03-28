/*
 * Simple testbench for UART.  Loop the rx and tx pins to each other and send
 * incrementing bytes, make sure that we receive what we expected.
 */

module testbench(input clk,input start,output tx);

reg [7:0] data = 8'b01000001;

wire tx_busy;
wire rdy;
wire [7:0] rxdata;
wire enable;
reg rdy_clr = 0;
//reg [1:0]state,nextstate;
localparam INIT=2'b00,
	           SEND=2'b01,
				  NEXT=2'b11,
				  MIDL=2'b10;
				  
assign enable = ~start;

uart test_uart(.din(data),
	       .wr_en(enable),
	       .clk_50m(clk),
	       .tx(tx),
	       .tx_busy(tx_busy),
	       .rx(loopback),
	       .rdy(rdy),
	       .rdy_clr(rdy_clr),
	       .dout(rxdata));

				  
always @(posedge clk or negedge start)begin
	if(!start) data <= 8'b01000001;
	else data <= 8'b10001000;
end


endmodule
