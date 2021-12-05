using Igalima.Engine.Injection;
using NUnit.Framework;

namespace Igalima.Engine.Tests.Injection;

[TestFixture]
public class DependencyProviderTests
{
    [Test]
    public void TestResolveNullableProperty()
    {
        var obj = new Object();
        var provider = new DependencyProvider();
        provider.Register(obj);

        var receiver = new Receiver();
        provider.Resolve(receiver);

        Assert.AreEqual(typeof(Object), receiver.TestObject?.GetType());
        Assert.AreEqual(-1, receiver.TestObject?.Value);
    }

    [Test]
    public void TestResolveMethodParameter()
    {
        var obj = new Object { Value = 12 };
        var provider = new DependencyProvider();

        provider.Register(obj);

        var receiver = new ReceiverWithMethod();
        provider.Resolve(receiver);

        Assert.AreEqual(typeof(Object), receiver.TestObject?.GetType());
        Assert.AreEqual(12, receiver.TestObject?.Value);
    }
}

public class Object
{
    public int Value { get; set; } = -1;
}

public class Receiver
{
    [Inject]
    public Object? TestObject { get; set; }
}

public class ReceiverWithMethod
{
    public Object? TestObject { get; private set; }

    [Resolve]
    public void Init(Object obj)
    {
        TestObject = obj;
    }
}