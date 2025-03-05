namespace Blue
{
	template<typename T, typename ...Args, typename std::enable_if<std::is_base_of<Shader, T>::value>::type*>
	inline bool ShaderLoader::Load(std::weak_ptr<T>& outShader, Args ...args)
	{
		// �ִ��� Ȯ�� �� ã������ ��ȯ.
		auto name = typeid(T).name();
		auto find = shaders.find(name);
		if (find != shaders.end())
		{
			outShader = std::static_pointer_cast<T>(find->second);
			return true;
		}

		// ������ ���� �� �����ڿ� �߰��ϰ� ��ȯ.
		std::shared_ptr<Shader> newShader = std::make_shared<T>(args...);
		shaders.insert(std::make_pair(name, newShader));
		outShader = std::static_pointer_cast<T>(newShader);
		return true;
	}
}
