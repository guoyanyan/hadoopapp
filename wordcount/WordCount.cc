#include"Pipes.hh"
#include"TemplateFactory.hh"
#include"StringUtils.hh"

// 100GµÄÊı¾İ£¬·Ö±ğ±£´æÔÚ5¸öÎÄ¼şÖĞ
// 5¸öÊı¾İÎÄ¼şµÄÄÚÈİ¾ùÎªÏàÍ¬µÄ¸ñÊ½
// ÎÄ¼şµÄÄÚÈİ´óÖÂÈçÏÂ:
// ABCDSDFKJDKF kkk 2890876
// SDKFJIEORUEW nnn 1231238
// LSFKDFSSDRDE bbb 9234999
// Ã¿Ò»ĞĞÄÚÈİÖĞ£¬Ê×ÏÈÊÇÒ»¸ö12×Ö½ÚµÄ×Ö·û´®£¬
// È»ºóÊÇÒ»¸ö3×Ö½ÚµÄ×Ö·û´®£¬
// È»ºóÊÇÒ»¸ö7¸öÊı×Ö×é³ÉµÄ×Ö·û´®¡£
// ×Ö·û´®Ö®¼äÊÇÓÃ¿Õ¸ñ·Ö¸ôµÄ
//
// ÎÊÌâ:
// ÔÚÕâ100GµÄÊı¾İÖĞ£¬ÇëÍ³¼Æ³öµÚ¶şÏî×Ö·û´®Îª"kkk"ºÍ"nnn"µÄÊı¾İ·Ö±ğÓĞ¶àÉÙÌõ£
// 

typedef std::vector<std::string> StringList;
class WordCountMap : public HadoopPipes::Mapper 
{
public:
  WordCountMap(HadoopPipes::TaskContext&context){}
  void map(HadoopPipes::MapContext&context) 
  {
    // ÕâÀïÊÇ·Ö¸î×Ö·û´®£¬Ã¿Ò»ĞĞÊı¾İÖĞµÄ¸÷ÏîÊÇÒÔ¿Õ¸ñÀ´·Ö¸îµÄ,
    // ·Ö¸îµÄ½á¹û±£´æµ½ÁËÒ»¸östd::vectorÖĞ
    // ÀıÈç: ABCDSDFKJDKF kkk 2890876
    // ÆäÖĞcontextWords[1]¼´ÎªÒªÍ³¼Æ
    StringList contextWords = HadoopUtils::splitString(context.getInputValue()," ");
    
    if("kkk"== contextWords[1])
    {
      context.emit("kkk","1");
    }
    else if("nnn"== contextWords[1]) 
    {
      context.emit("nnn","1");
    }
    
  }
};
 
class WordCountReduce : public HadoopPipes::Reducer 
{
public:
  WordCountReduce(HadoopPipes::TaskContext&context){}
  void reduce(HadoopPipes::ReduceContext&context)
  {
    int sum=0;
    while(context.nextValue()) 
    {
      sum++;
    }
    context.emit(context.getInputKey(), HadoopUtils::toString(sum));
  }
};
 
int main(int argc,char**argv)
{
  return HadoopPipes::runTask(HadoopPipes::TemplateFactory<WordCountMap, WordCountReduce>());
}
