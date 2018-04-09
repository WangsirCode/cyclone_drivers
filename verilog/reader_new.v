`timescale 1ns / 1ps

//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:55:33 03/22/2018 
// Design Name: 
// Module Name:    Reader 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module Reader(
	sysclk,
	counter,
	//clock,      //The clock used to collect the results of AD
	start,      //start working signal
	rst_n,      //reset signal
	data_ad,    //the results of AD module
	ready,      //鍙戠粰CPU缁撴潫鏈疆鏁版嵁鍙戦€
	tx
);
	input sysclk;
	//input clock;
	input start;
	input rst_n;
	input [19:0] counter;
	input [11:0] data_ad;
	output reg ready;
	output tx;
	 
	wire ad_clk;
	reg [5:0] i;
	reg [5:0] j;
	reg [511:0] Data;
	reg [7:0] tx_data;
	reg start_tx;
	wire tx_busy;
	wire rx,rdy,rdy_clr,dout;
	reg [2:0] state, next_state;
	 
	localparam  INIT  = 3'b000,
					READ  = 3'b001,
					SEND  = 3'b010,
					END   = 3'b100,
					MIDIA = 3'b101,
					WAIT  = 3'b110,
					WAIT_READ = 3'b011;
	
	localparam SIZE = 32;
	localparam SEND_SIZE = 64;
					
					
	always@(posedge sysclk or negedge rst_n) begin
		state <= (!rst_n) ? INIT : next_state;
	end
	
	
	always@ (state)begin
		case(state)
			INIT:
				next_state =  (start?) WAIT_READ:INIT;
			WAIT_READ:
				next_state = (ad_clk == 1)? READ:state;
	
	
	
	
	
	
	
//	always@(start or state or clock or tx_busy)begin
	always@(posedge sysclk)begin
		case(state)
			INIT:begin
				i <= 6'b0;
				j <= 6'b0;
				ready <= 0;
				Data <= 512'b0;
				start_tx <= 0;
				tx_data <= 8'b0;
				if(start)begin
					next_state <= WAIT_READ;
				end
				else 
					next_state <= INIT;
			end
			WAIT_READ:begin
				next_state <= (ad_clk == 1)? READ:state;
			end
			READ:begin 
				if(i == SIZE) begin
					tx_data <= Data[7:0];
					Data <= {8'b0,Data[511:8]};
					start_tx <= 1;
					j <= 6'd0;
					next_state <= WAIT;
				end
				else begin
					Data <= {4'b0000,data_ad,Data[511:16]};
					i <= i + 1'b1;
					tx_data <= tx_data;
					start_tx <= start_tx;
					next_state <= WAIT_READ;
				end
			end
			WAIT:begin
				i <= i;
				j <= j;
				tx_data <= tx_data;
				start_tx <= start_tx;
				Data <= Data;
				next_state <= (tx_busy == 1)?SEND:state;
			end
			SEND:begin
				if(!tx_busy)begin
					start_tx <= 0;
					tx_data <= Data[7:0];
					Data <= {8'b0,Data[511:8]};
					j <= j;
					i <= i;
					next_state <= (j == SEND_SIZE - 2)? END : MIDIA;
				end
				else begin
					i <= i;
					j <= j;
					tx_data <= tx_data;
					start_tx <= start_tx;
					Data <= Data;
					next_state <= state;	
				end
			end
			MIDIA:begin
				i <= i;
				j <= j + 1'b1;
				tx_data <= tx_data;
				start_tx <= 1;
				Data <= Data;
				next_state <= (tx_busy == 1)?SEND:state;
			end

			END:begin
				i <= i;
				j <= j;
				ready <= 1;
				start_tx <= 0;
				tx_data <= tx_data;
				if(start == 0)
					next_state <= INIT;
				else
					next_state <= END;
			end
			default:
				next_state <= INIT;
		endcase
	end
	uart uart
	(
		.din(tx_data),
		.wr_en(start_tx),
	   .clk_50m(sysclk),
	   .tx(tx),
	   .tx_busy(tx_busy),
	   .rx(rx),
	   .rdy(rdy),
	   .rdy_clr(rdy_clr),
	   .dout(dout)
		);
	clk_gen ad_clock
	(
		.counter(counter),
		.clk(sysclk),
		.ad_clk(ad_clk)
	);
endmodule
