module clk_gen(
	counter, clk, ad_clk
);

input [19:0]counter;
input clk;
output ad_clk;

reg [19:0]acc = 0;
wire equal;

comparator compare(
	.maxcounter(counter),
	.counter(acc),
	.result(equal)
);

assign ad_clk = (acc == 20'd0);

always @(posedge clk) begin
	if (equal)
		acc <= 0;
	else
		acc <= acc + 20'b1;
end

endmodule