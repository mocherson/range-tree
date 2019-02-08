library(IRanges)
print(R.Version()$version.string)
# print(BiocManager::version())
readAsRanges<-function(filename){
    cat(sprintf('reading file: %s\n',filename))
    itvs = read.table(filename)
    rg = IRanges(start=itvs$V1, end=itvs$V2)
    return(rg)
}


cat(paste('chromosome','any','within','start','end','equal'), file="timeout_gr.txt",sep="\n",append=TRUE)
for (chr in c(1:22, 'X')) {
    datafile=sprintf('/home/shared_data/ENCODE/unqitv/chr%s.txt',chr)
    queryfile=sprintf('/home/shared_data/gnomad/gnomAD/vcf/genomes/genomes.r2.0.1.sites.%s.csv',chr)
    gr1 = readAsRanges(datafile)
    gr1 = NCList(gr1)
    gr2 = readAsRanges(queryfile)
    gc()
    
    cat(sprintf('find any overlaps\n'))    
    timestart<-Sys.time()
    findOverlaps(gr1, gr2,type='any')
    timeend<-Sys.time()
    t_any = as.double(timeend-timestart, units = "secs" )
    gc()
    
    cat(sprintf('find within overlaps\n')) 
    timestart<-Sys.time()
    findOverlaps(gr1, gr2,type='within')  # 4 relations: d, s, f, e
    timeend<-Sys.time()
    t_within = as.double(timeend-timestart, units = "secs" )
    gc()
    
    cat(sprintf('find start overlaps\n')) 
    timestart<-Sys.time()
    findOverlaps(gr1, gr2,type='start')  # 3 relations: s, si, e
    timeend<-Sys.time()
    t_start = as.double(timeend-timestart, units = "secs" )
    gc()
    
    cat(sprintf('find end overlaps\n')) 
    timestart<-Sys.time()
    findOverlaps(gr1, gr2,type='end')  # 3 relations: f, fi, e
    timeend<-Sys.time()
    t_end = as.double(timeend-timestart, units = "secs" )
    
    cat(sprintf('find equal overlaps\n')) 
    timestart<-Sys.time()
    findOverlaps(gr1, gr2,type='equal')  # 1 relations: e
    timeend<-Sys.time()
    t_equal = as.double(timeend-timestart, units = "secs" )
    gc()
    
    cat(paste(chr, t_any,t_within,t_start,t_end,t_equal), file="timeout_gr.txt",sep="\n",append=TRUE)
}    
