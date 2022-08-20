# Factory Method Pattern
- [정리 글](정리-글)
- [각 구성 요소의 역할](각-구성-요소의-역할)
- [실행 결과](실행-결과)

## 정리 글
- [팩토리 메서드(Factory Method)](https://www.notion.so/Factory-Method-8c291dea1c9f49c28c8f8721a7ade575)

## 각 구성 요소의 역할
- [Creator](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Factory%20Method%20Pattern/Creator)
    - 구현
        - 각각의 Product 클래스들의 생성자를 호출할 서브 클래스의 FactoryMethod 함수들의 원형 함수인 FactoryMethod 함수를 선언하고 있는 클래스입니다. 
        - Factory Method 함수는 Creator 클래스에서 일반적으로 순수 가상함수로 구현됩니다. 하지만 모든 서브 클래스가 공유하는 생성자에 들어가야할 내용이 있다면 해당 사항을 포함하여 Creator 클래스 내에서 구현될 수도 있습니다.
    - 역할
        - 여러 ConcreteCreater들의 부모 클래스가 되는 클래스입니다.
        - 앞서 언급한 FactoryMethod 함수뿐만 아니라 생성한 ConcreteProduct를 활용하는 여러 다른 함수들도 서브 클래스들이 재정의 가능하도록 하도록 하여 각 ConcreteCreator들에 적절한 ConcreteProduct를 활용하도록 할 수 있습니다.
- [ConcreteCreator들](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Factory%20Method%20Pattern/ConcreteCreators)
    - 구현
        - Product의 서브클래스들인 ConcreteProducts를 생성하기 위한 생성자를 호출하는 클래스들입니다.
    - 역할
        - Creator에서 정의된 FactoryMethod 함수를 재정의하여 자신(각각의 ConcreteCreator)에 맞는 ConcreteProduct가 생성합니다.
        - 또한 생성한 적절한 ConcreteProduct를 활용하여 여러 작업들을 구현하여 
- [Product](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Factory%20Method%20Pattern/Product)
    - 구현
        - 모든 ConcreteProduct들이 상속받을 부모 클래스(혹은 인터페이스)입니다.
        - 상속 받을 모든 클래스가 공유하는 내용이면 이 클래스 내부에 구현하고, 나머지 서브 클래스 별로 달라지는 내용에 대해서는 각각의 서브 클래스가 오버라이딩 하여 구현하도록 순수 가상 함수로 남겨두게 됩니다.
    - 역할
        - ConcreteCreator들에서 활용될 ConcreteProduct들의 부모 클래스로, 각각의 ConcreteCreator들에서는 실제로는 각각 자신에 맞는 ConcreteProduct를 생성하지만, 부모 클래스인 Product의 포인터 형태로 저장하거나 연결하여 다형성을 통해 적절한 ConcreteProduct로의 연결이 가능하도록 합니다.
- [ConcreteProduct들](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Factory%20Method%20Pattern/ConcreteProducts)
    - 구현
        - Product 클래스를 상속받아 구체적인 객체에 대한 구현을 진행하는 클래스들입니다.
- [테스트 코드](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/blob/master/Creational%20Patterns/Factory%20Method%20Pattern/test.cpp)

## 효과
- 프로젝트를 확장하여 새로운 ConcreteProducts가 필요하다고 하면, 다른 코드의 수정 필요 없이 Product를 상속받은 새로운 클래스와, 해당 클래스에 대한 새로운 CocreateCreator만 추가해주면 됩니다. 만약 Factory Method 패턴을 사용하지 않았다면 각 Product를 생성, 사용하는 여러 곳들마다 조건문이 산개해 있을 것이며, 그 조건문들마다 새로운 Product에 대한 조건을 추가해야할 것입니다.

## 실행 결과
![Factory method pattern result](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/blob/master/result%20images/Factory%20method%20pattern%20result.png)
