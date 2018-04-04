module comparator(
	maxcounter,counter,result
);
input [19:0]maxcounter;
input [19:0]counter;
output result;

assign result = ((maxcounter ^ counter) == 0);

endmodule