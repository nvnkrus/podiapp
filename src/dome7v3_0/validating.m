% ============================================================
%    PODI-RBF PROGRAM FOR HEMISPHERE DOME PROBLEM

% Target: approximate the displacement and von-Mises
% stress fields of the hyperelastic dome during the
% indentation process. The indenter object is rigid.
% In the file `parameter.csv`, users can vary
% 	- the contact location `x_c` (first 3 numbers)
% 	- indentation depth (last numbers) `d_c` in [-20,-5] mm.
% The approximated solutions by PODI-RBF method are obtained
% in online stage and stored in `result` folder.
%             -----------------         
% For evaluation, Abaqus solutions of 32 cases are provided.
% These cases are related to 2 new contact locations: 
% 	P1: -29.065, 41.485, 21.429
% 	P2: 9.7533, 53.479, -8.3564
% and 16 values of indentation depth from 5 mm to 20 mm

%% 32 validating cases
paraval_new = ...
	[   -2.7437   54.9315   -0.0051  -17.5000
       -2.7437   54.9315   -0.0051  -12.5000
       -2.7437   54.9315   -0.0051   -7.5000
       36.3873   41.1143   -3.2523  -17.5000
       36.3873   41.1143   -3.2523  -12.5000
       36.3873   41.1143   -3.2523   -7.5000
       15.8607   40.7905   33.3103  -17.5000
       15.8607   40.7905   33.3103  -12.5000
       15.8607   40.7905   33.3103   -7.5000
        9.7251   40.9166  -35.4437  -17.5000
        9.7251   40.9166  -35.4437  -12.5000
        9.7251   40.9166  -35.4437   -7.5000
      -25.9497   41.2262   25.5347  -17.5000
      -25.9497   41.2262   25.5347  -12.5000
      -25.9497   41.2262   25.5347   -7.5000
      -25.9477   41.2216  -25.5440  -17.5000
      -25.9477   41.2216  -25.5440  -12.5000
      -25.9477   41.2216  -25.5440   -7.5000
      -35.4103   42.0845   -0.0007  -17.5000
      -35.4103   42.0845   -0.0007  -12.5000
      -35.4103   42.0845   -0.0007   -7.5000
       17.8560   50.4220  -12.7979  -17.5000
       17.8560   50.4220  -12.7979  -12.5000
       17.8560   50.4220  -12.7979   -7.5000
       20.2040   49.5113   12.8619  -17.5000
       20.2040   49.5113   12.8619  -12.5000
       20.2040   49.5113   12.8619   -7.5000
       -4.6512   48.1864   26.1043  -17.5000
       -4.6512   48.1864   26.1043  -12.5000
       -4.6512   48.1864   26.1043   -7.5000];
nparaval = size(paraval_new,1);

%% Test the software only
	valIDs = 1:nparaval; 	% use this if you want to validate all 30 cases
	% valIDs = 1; 			% modify this if you want to test a subset of cases

	%% Validating in a loop
	for id = 1:length(valIDs)
		valID = valIDs(id);
		paras = paraval_new(valID,:);
		csvwrite('parameter.csv', paras);
		system('./run_main.sh');
	end

%% Test the software only + visualization
% it is recommended to run one case at a time
	valIDs = 1; 				% modify to choose a test case

	%% Validating in a loop
	for id = 1:length(valIDs)
		valID = valIDs(id);
		paras = paraval_new(valID,:);
		csvwrite('parameter.csv', paras);
		system('./run_main.sh');

		post_process;
	end