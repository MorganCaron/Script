#pragma once

#include <numeric>

#include <Language/AST/Function/Function.hpp>
#include <Language/AST/Variable/VariableScope.hpp>

using namespace std::string_literals;

namespace Language::AST::Function
{
	struct FunctionSignature
	{
		const std::string name;
		const std::vector<CppUtils::Type::TypeId> argumentTypes;
		const std::string printable;
		const CppUtils::Type::TypeId type;

		FunctionSignature(std::string c_name, std::vector<CppUtils::Type::TypeId> c_argumentTypes = {}):
			name{std::move(c_name)},
			argumentTypes{std::move(c_argumentTypes)},
			printable{getPrintable()},
			type{printable}
		{}

		[[nodiscard]] bool operator==(const FunctionSignature& rhs) const
		{
			return name == rhs.name && argumentTypes == rhs.argumentTypes;
		}

		struct hash_fn
		{
			std::size_t operator()(const FunctionSignature &functionSignature) const
			{
				return functionSignature.type.id;
			}
		};

	private:
		[[nodiscard]] inline std::string getPrintable() const
		{
			return name + "(" + std::accumulate(argumentTypes.begin(), argumentTypes.end(), std::string{},
				[](std::string buffer, const CppUtils::Type::TypeId &argumentType) {
					return buffer.empty() ? argumentType.name.data() : (buffer + "," + argumentType.name.data());
				}) + ")";
		}
	};

	using FunctionType = ITFunction<std::unique_ptr<Type::IValue>(const Type::Args&)>;

	constexpr static const Scope::ScopeType FunctionScopeType = 2;

	class FunctionScope: public Variable::VariableScope
	{
	public:
		FunctionScope(BaseScope* scope = nullptr, Scope::ScopeType scopeType = FunctionScopeType):
			Variable::VariableScope{scope, scopeType}
		{}

		FunctionScope(const FunctionScope& src):
			Variable::VariableScope{src}
		{
			for (const auto& [key, value] : src.getFunctions())
				addFunction(key, value->cloneFunction());
		}

		FunctionScope(FunctionScope&&) noexcept = default;
		virtual ~FunctionScope() = default;

		FunctionScope& operator=(const FunctionScope& rhs)
		{
			Variable::VariableScope::operator=(rhs);
			for (const auto& [key, value] : rhs.getFunctions())
				addFunction(key, value->cloneFunction());
			return *this;
		}

		FunctionScope& operator=(FunctionScope&&) noexcept = default;

		[[nodiscard]] bool functionExists(const FunctionSignature& functionSignature) const
		{
			if (m_functions.find(functionSignature) != m_functions.end())
				return true;
			if (hasScope())
				return dynamic_cast<const FunctionScope&>(getScope().findScope(getType())).functionExists(functionSignature);
			return false;
		}

		inline void addFunction(const FunctionSignature& functionSignature, std::unique_ptr<FunctionType>&& function)
		{
			m_functions[functionSignature] = std::move(function);
		}

		inline void resetFunctions() noexcept
		{
			m_functions.clear();
		}

		[[nodiscard]] inline const std::unordered_map<FunctionSignature, std::unique_ptr<FunctionType>, FunctionSignature::hash_fn>& getFunctions() const noexcept
		{
			return m_functions;
		}

		[[nodiscard]] FunctionType& getFunction(const FunctionSignature& functionSignature) const
		{
			const auto it = m_functions.find(functionSignature);
			if (it != m_functions.end())
				return *it->second;
			if (!hasScope())
				throw std::runtime_error{"Unknown function "s + functionSignature.printable};
			return dynamic_cast<const FunctionScope&>(getScope().findScope(getType())).getFunction(functionSignature);
		}

	private:
		std::unordered_map<FunctionSignature, std::unique_ptr<FunctionType>, FunctionSignature::hash_fn> m_functions;
	};
}
