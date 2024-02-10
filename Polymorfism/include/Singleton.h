template<class T>
class Singleton {
public:
	static T* getInstance() {
		if (instance == nullptr) {
			instance == new T();
		}
		return instance;
	}
private:
	Singleton() {} = delete;
	static T* instance{ nullptr };
};