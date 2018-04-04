module reader_test(sysclk,rst_n,start,tx,LED1,LED2,LED3);

	input sysclk,rst_n;
	output tx;
	output LED1;
	output LED2;
	output LED3;
	input start;
	reg [11:0] data_ad;
	wire ready;
	wire enable;
	reg [19:0] counter;
	Reader reader(
	.sysclk(sysclk),
	.counter(counter),
	.start(enable),
	.rst_n(rst_n),
	.data_ad(data_ad),
	.ready(ready),
	.tx(tx)
	);
	
	assign enable = ~start;
	assign LED1 = ~rst_n;
	assign LED2 = ~start;
	assign LED3 = ~ready;
	
	always@(posedge sysclk)begin
		if(!rst_n)begin
			data_ad <= 12'b0101_1111_0011;
			counter <= 10'd1000;
		end
//		else
//			data_ad <= data_ad + 1;
			
	end
endmodule
