#!/bin/sh

for i in 1 2 3 4 5
do
	./Test input$i.txt output$i.txt	 forward visualsOf 500000
done