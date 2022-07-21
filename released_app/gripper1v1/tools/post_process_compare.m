fprintf('==============================================\n');
fprintf('Abaqus solution is available for this case:\n')
fprintf('valID %d: h = %d, theta_x = %d, d_x = %.2f\n', ...
		valID, paras(1), paras(2), paras(3));

%% Abaqus solution
disp_true = dispval(:,valID);
mises_true = misesval(:,valID);

%% evaluate the errors of displacement and stress
% displacement
err_rtne = rtne(disp_new,disp_true)*100; % about 1%
err_rmse = rmse(disp_new,disp_true);

fprintf('Displacement:\n');
fprintf('\tError L2: %.2f %%\n',err_rtne);
fprintf('\tError rmse: %.2g \n',err_rmse);
fprintf('\tMax value : Abaqus %.2g, PODI-RBF %.2g \n', ...
	max(abs(disp_true)),max(abs(disp_new)));

% mises stress
err_rtne = rtne(mises_new,mises_true)*100; % about 1%
err_rmse = rmse(mises_new,mises_true);

fprintf('von Mises stress:\n');
fprintf('\tError L2: %.2f %%\n',err_rtne);
fprintf('\tError rmse: %.2g \n',err_rmse);
fprintf('\tMax value : Abaqus %.2g, PODI-RBF %.2g \n', ...
	max(abs(mises_true)),max(abs(mises_new)));

figure;
dispmat = reshape(disp_new,3,nnode)';
% podi displacement - Ux
subplot(2,4,1); 
dispmag = dispmat(:,1);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Ux');

% podi displacement - Uy
subplot(2,4,2); 
dispmag = dispmat(:,2);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Uy');

% podi displacement - Uz
subplot(2,4,3); 
dispmag = dispmat(:,3);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Uz');

% podi displacement - von-Mises
subplot(2,4,4); 
dispmag = mises_new;
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - von-Mises');


dispmat = reshape(disp_true,3,nnode)'; 
% Abaqus displacement - Ux
subplot(2,4,5); 
dispmag = dispmat(:,1);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('Abaqus solution - Ux');

% Abaqus displacement - Uy
subplot(2,4,6); 
dispmag = dispmat(:,2);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('Abaqus solution - Uy');

% Abaqus displacement - Uz
subplot(2,4,7); 
dispmag = dispmat(:,3);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('Abaqus solution - Uz');

% Abaqus displacement - von-Mises
subplot(2,4,8); 
dispmag = mises_true;
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('Abaqus solution - von-Mises');

set(gcf,'Position',[1,1,1818,1003]);