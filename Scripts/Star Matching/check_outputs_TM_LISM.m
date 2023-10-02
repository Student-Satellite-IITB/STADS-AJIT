%no outputs in 26, 39, 61, 74, 80
clear
mismatch_t = []         %t for testcase
tot_matches_t = []
b = []
store_iter = []
for testcase = [1:83]    
    mismatched_stars = 0
    tot_stars = 0
    for iter = 1 : 100
        mFileName = sprintf('./out_CSV/out_TM_LISM_csv/out_TM_LISM_%s/OILS_iter_info_%s.csv', string(testcase), string(iter));
        mFile = readtable(mFileName, 'PreserveVariableNames', true);
        matched_stars = height(mFile)
        if (height(mFile) ~= 1)
            mFile_data = mFile(:, 3:10)
            mdata = table2array(mFile_data);
            if (iter == 100)
                mdata(length(mdata(:,1)), :) = 0
            end
            match_check = mdata(:, 1)- mdata(:, 2)
            A = find(match_check > 0)
            mismatched_stars = mismatched_stars + length(A)
            tot_stars = tot_stars + length(mdata(:,1))
        end 
    end
    mismatch_t = [mismatch_t ; mismatched_stars]
    tot_matches_t = [tot_matches_t ; tot_stars - mismatched_stars ]
end
