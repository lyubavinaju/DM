using System;

namespace ClassLibrary1
{
    public class Hello
    {
        public static void Main()
        {
string s1 = "World";
            string s2 = "Hello";
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