fprintf('==============================================\n');
fprintf('Abaqus solution is available for this case:\n')
fprintf('valID %d: d = %.4f\n', valID, paras);

%% Abaqus solution
snap_true = zeros(nnode,4);
snap_true(:,1:3) = reshape(dispval(:,valID),3,nnode)';
snap_true(:,4) = misesval(:,valID);

%% PODI-RBF solution
snap_new = zeros(nnode,4);
snap_new(:,1:3) = reshape(disp_new,3,nnode)';
snap_new(:,4) = mises_new;

%% evaluate the errors of displacement and stress
temp1 = snap_new(:); temp2 = snap_true(:);
% displacement
temp11 = temp1(1:3*nnode); 
temp21 = temp2(1:3*nnode); 
err_rtne = rtne(temp11,temp21)*100; % about 1%
err_rmse = rmse(temp11,temp21);

fprintf('Displacement:\n');
fprintf('\tError L2: %.2f %%\n',err_rtne);
fprintf('\tError rmse: %.2g \n',err_rmse);
fprintf('\tMax value : Abaqus %.2g, PODI-RBF %.2g \n', ...
	max(abs(temp21)),max(abs(temp11)));

% mises stress
temp12 = temp1(1+3*nnode:end); 
temp22 = temp2(1+3*nnode:end); 
err_rtne = rtne(temp12,temp22)*100; % about 1%
err_rmse = rmse(temp12,temp22);

fprintf('von Mises stress:\n');
fprintf('\tError L2: %.2f %%\n',err_rtne);
fprintf('\tError rmse: %.2g \n',err_rmse);
fprintf('\tMax value : Abaqus %.2g, PODI-RBF %.2g \n', ...
	max(abs(temp22)),max(abs(temp12)));

figure;
dispmat = snap_new(:,1:3);
% podi displacement - Ux
subplot(2,4,1); 
dispmag = snap_new(:,1);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Ux');

% podi displacement - Uy
subplot(2,4,2); 
dispmag = snap_new(:,2);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Uy');

% podi displacement - Uz
subplot(2,4,3); 
dispmag = snap_new(:,3);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - Uz');

% podi displacement - von-Mises
subplot(2,4,4); 
dispmag = snap_new(:,4);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('PODI-RBF solution - von-Mises');


dispmat = snap_true(:,1:3);
% Abaqus displacement - Ux
subplot(2,4,5); 
dispmag = snap_true(:,1);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('Abaqus solution - Ux');

% Abaqus displacement - Uy
subplot(2,4,6); 
dispmag = snap_true(:,2);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('Abaqus solution - Uy');

% Abaqus displacement - Uz
subplot(2,4,7); 
dispmag = snap_true(:,3);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('Abaqus solution - Uz');

% Abaqus displacement - von-Mises
subplot(2,4,8); 
dispmag = snap_true(:,4);
gcrd_deform = gcrd + dispmat;
h = trisurf(bfaces,gcrd_deform(:,1),gcrd_deform(:,2),...
	gcrd_deform(:,3),dispmag);
set(h,'LineStyle','none','FaceAlpha',1);
axis image; box on; colorbar; view([0,90]);
xlabel('x'); ylabel('y'); zlabel('z');
title('Abaqus solution - von-Mises');

set(gcf,'Position',[1,1,1818,1003]);