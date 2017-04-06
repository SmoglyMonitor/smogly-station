class Config
{
  const static int PARAM_LEN = 130;
public:
  void read(const char* fileName);
  void save(const char* fileName);
  void mount();
  void reset();
  char apiEndpoint[PARAM_LEN];
  char token[PARAM_LEN];
};
