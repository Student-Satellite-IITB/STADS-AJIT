%select a file
%convert the sis_output table to array
%make an array
%strore the required data in required format
%export the data to text file with commas

N = 100;%number of files to be read
for i = 1:N
    inputfile = "matout_run13_6.5/SIS_iter_" + i + ".mat";
    outfilename = "textout_run13_6.5/SIS_iter_" + i + ".txt";
    myFile = load(inputfile);
    data = table2array(myFile.sis_output.data_table);
    estdata = zeros(3,2*height(myFile.sis_output.data_table));
    for j = 1:3
    estdata(j,1:height(myFile.sis_output.data_table)) =  myFile.sis_output.data_table.r0(1:height(myFile.sis_output.data_table),j);
    estdata(j,(height(myFile.sis_output.data_table)+1:end)) =  myFile.sis_output.data_table.r3(1:height(myFile.sis_output.data_table),j);
    end
    writematrix(estdata, outfilename);
end