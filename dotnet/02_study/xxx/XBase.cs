using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _02_study.xxx
{
    internal class XBase
    {
        private int m_id;
        private string m_name;

        public XBase(int paramId, string paramName)
        {
            m_id = paramId;
            m_name = paramName;
        }

        public string Name
        {
            get { return m_name; }
            set { m_name = value; }
        }
        public int Id
        {
            get { return m_id; }
            set
            {
                if (value > 100)
                {
                    m_id = value;
                }
                else
                {
                    m_id = -value;
                }
            }
        }
    }
}
