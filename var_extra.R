

#library(parallel)
library(VariantAnnotation)


#path='.'
path='/home/shared_data/gnomad/gnomAD/vcf/genomes'
files=dir(path,pattern='\\.vcf.gz$',full.names=TRUE)


extra<- function(file){

    cat('Reading...',file,'\n')
    vcf<- readVcf(file,'hg19');
    rgs=as.data.frame(ranges(vcf));
    chr=as.data.frame(seqnames(vcf));
    content=data.frame(chr,rgs$start,rgs$end);
    cat('uniquing...\n')
    unq_itv=unique(content);
    cat('writing...\n')
    write.table(unq_itv,file=gsub('vcf.gz','csv',file),quote=F,sep=',',row.names=F,col.names=F);
    cat('File',file,'done.\n');
}

fs=files[!file.exists(gsub('vcf.gz','csv',files))];
#cl <- makeCluster(9,outfile='debug.txt');
#parLapply(cl,fs,extra);
lapply(fs,extra);

#stopCluster(cl)