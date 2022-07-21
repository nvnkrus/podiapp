fname = fullfile('database','podi','mises','gmat.bin');
gmat = binread(fname);

fname = fullfile('database','podi','mises','misestrain.bin');
misestrain = binread(fname);
[phi,s,amat,d] = pod_full(snapmat,'econ',0.9995,true);
bmat = amat/gmat;

fname1 = fullfile('database','podi','mises','phi.bin');
fname2 = fullfile('database','podi','mises','bmat.bin');
binwrite(fname1,phi);
binwrite(fname2,bmat);
