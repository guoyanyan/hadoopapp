#include"Pipes.hh"
#include"TemplateFactory.hh"
#include"StringUtils.hh"

// 100G�����ݣ��ֱ𱣴���5���ļ���
// 5�������ļ������ݾ�Ϊ��ͬ�ĸ�ʽ
// �ļ������ݴ�������:
// ABCDSDFKJDKF kkk 2890876
// SDKFJIEORUEW nnn 1231238
// LSFKDFSSDRDE bbb 9234999
// ÿһ�������У�������һ��12�ֽڵ��ַ�����
// Ȼ����һ��3�ֽڵ��ַ�����
// Ȼ����һ��7��������ɵ��ַ�����
// �ַ���֮�����ÿո�ָ���
//
// ����:
// ����100G�������У���ͳ�Ƴ��ڶ����ַ���Ϊ"kkk"��"nnn"�����ݷֱ��ж������
// 

typedef std::vector<std::string> StringList;
class WordCountMap : public HadoopPipes::Mapper 
{
public:
  WordCountMap(HadoopPipes::TaskContext&context){}
  void map(HadoopPipes::MapContext&context) 
  {
    // �����Ƿָ��ַ�����ÿһ�������еĸ������Կո����ָ��,
    // �ָ�Ľ�����浽��һ��std::vector��
    // ����: ABCDSDFKJDKF kkk 2890876
    // ����contextWords[1]��ΪҪͳ��
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
