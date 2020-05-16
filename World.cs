using System;

namespace ClassLibrary1
{
    public class World
    {
        public static void Main()
        {
string s1 = "Hello";
            string s2 = "World";
            string main = @"using System;

namespace ClassLibrary1
{{
    public class {3}
    {{
        public static void Main()
        {{
string s1 = {1}{2}{1};
            string s2 = {1}{3}{1};
            string main = @{1}{0}{1};
            Console.Write(main,main,'{1}',s2,s1);
        }}
    }}
}}";
            Console.Write(main,main,'"',s2,s1);
        }
    }
}