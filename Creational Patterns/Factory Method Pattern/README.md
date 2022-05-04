# Factory Method Pattern
- [정리 글](정리-글)
- [각 구성 요소의 역할](각-구성-요소의-역할)
- [실행 결과](실행-결과)

## 정리 글
- [팩토리 메서드(Factory Method)](https://www.notion.so/Factory-Method-8c291dea1c9f49c28c8f8721a7ade575)

## 각 구성 요소의 역할
- [Creator](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Factory%20Method%20Pattern/Creator)
    - 각각의 서브 클래스들의 생성자를 호출할 서브 클래스의 원형 함수인 FactoryMethod 함수를 선언하고 있는 클래스입니다.
    - Factory Method 함수는 Creator 클래스에서 일반적으로 순수 가상함수로 구현됩니다. 하지만 모든 서브 클래스가 공유하는 생성자에 들어가야할 내용이 있다면 해당 사항을 포함하여 Creator 클래스 내에서 구현될 수도 있습니다.
- [ConcreateCreator들](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Factory%20Method%20Pattern/ConcreteCreators)
    - Product의 서브클래스들인 ConcreteProducts를 생성하기 위한 생성자를 호출하는 클래스들입니다.
    - 만약 프로젝트를 확장하여 새로운 ConcreteProducts가 필요하다고 하면, 다른 코드의 수정 필요 없이 Product를 상속받은 새로운 클래스와, 해당 클래스에 대한 새로운 CocreateCreator만 추가해주면 됩니다.
- [Product](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Factory%20Method%20Pattern/Product)
    - 모든 ConcreteProduct들이 상속받을 부모 클래스(혹은 인터페이스)입니다.
    - 상속 받을 모든 클래스가 공유하는 내용이면 이 클래스 내부에 구현하고, 나머지 서브 클래스 별로 달라지는 내용에 대해서는 각각의 서브 클래스가 오버라이딩 하여 구현하도록 순수 가상 함수로 남겨두게 됩니다.
- [ConcreteProducts](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/tree/master/Creational%20Patterns/Factory%20Method%20Pattern/ConcreteProducts)
    - Product 클래스를 상속받아 구체적인 객체에 대한 구현을 진행하는 클래스들입니다.
    - 만약 프로젝트를 확장하여 새로운 ConcreteProducts가 필요하다고 하면, 다른 코드의 수정 필요 없이 Product를 상속받은 새로운 클래스와, 해당 클래스에 대한 새로운 CocreateCreator만 추가해주면 됩니다.
- [테스트 코드](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/blob/master/Creational%20Patterns/Factory%20Method%20Pattern/test.cpp)

## 실행 결과
![Factory method pattern result](https://github.com/jiy12345/DesiginPatterns_In_CPlusPlus/blob/master/result%20images/Factory%20method%20pattern%20result.png)
