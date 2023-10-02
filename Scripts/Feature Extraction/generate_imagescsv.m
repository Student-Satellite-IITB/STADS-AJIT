for i = 1 : 83
    for j = 1 : 100
        imagemat = load(sprintf('./SIS_runs/SIS run-%s/Output/SIS_iter_%s.mat',string(i), string(j)));

        IMAGE = imagemat.sis_output.image;
        %no need to pad zeroes here. included in preprocess_image.py
        % row = zeros(1,808);
        % column = zeros(610,1);
        % IMAGE = [row;IMAGE;row];
        % padded_IMAGE =[column IMAGE column];

    writematrix(IMAGE, sprintf('./Images/Testcase_%s/txt/image_%s.txt',string(i),string(j)));
    end
end