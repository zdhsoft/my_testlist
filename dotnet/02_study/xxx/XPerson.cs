using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _02_study.xxx
{
    internal class XPerson : XBase
    {
        private int m_age;
        public XPerson() : base(100, "XPerson")
        {
            m_age = 0;
        }

        public int Age
        {
            get
            {
                return m_age;
            }
            set
            {
                if (value < 0)
                {
                    m_age = 0;
                }
                else if (value > 100)
                {
                    m_age = 100;
                }
                else
                {
                    m_age = value;
                }
            }
        }
    }
}
