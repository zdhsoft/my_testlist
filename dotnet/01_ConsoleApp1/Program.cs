using System;
using System.Collections;

namespace Simple
{
    interface ITest
    {
        string GetName();
        string GetDescription();

        int GetId();
    }


    class XTest : ITest
    {
        private int m_id;
        private string m_name;
        private string m_description;

        public XTest(int paramId = 0, string paramName = "", string paramDescription = "")
        {
            m_id = paramId;
            m_name = paramName;
            m_description = paramDescription;
        }


        public string GetDescription()
        {
            return m_description;
        }

        public void SetDescription(string paramDescription)
        {
            m_description = paramDescription;
        }

        public int GetId()
        {
            return m_id;
        }

        public string GetName()
        {
            return m_name;
        }

        public override string ToString()
        {
            return String.Format("id:{0}, name:{1}, desc:{2}", m_id, m_name, m_description);

        }
    }


    class Empty
    {
        public override string ToString()
        {
            return "hello MyName is Empty";

        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is C#");
            var data = new ArrayList(10)
            {
                "Visual Basic",
                344,
                55,
                new Empty()
            };
            data.Remove(55);

            foreach (object el in data)
            {
                Console.WriteLine(el);
            }

            int m = 100;
            for (int i = 0; i < m; i++)
            {
                Console.WriteLine("%d", i);
            }
            
        }

}
}