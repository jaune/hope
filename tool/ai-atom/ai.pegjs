Start
 = _? items:DesciptionItem* _?  { return items; }

DesciptionItem
 = Step
 / Table
 / TableItem 
 / Need
 / Alias

Alias
 = "alias" _ cpp:CppNames _ name:Name _? ";" _?                          { return { type: 'alias', cpp: cpp, name: name }; }
 
CppNames
 = begin:CppName "::" end:CppNames                                       { return [begin].concat(end).join('::'); }
 / CppName

CppName
 = Name

Need
 = "need" _ name:Name _? ";" _?                                           { return { type: 'need', name: name }; }

Table
 = "table" _ name:Name _? "{" _? "}" _?                                   { return { type: 'table', name: name, content: [] }; }
 / "table" _ name:Name _? "{" _? content:TableContent* _? "}" _?          { return { type: 'table', name: name, content: content }; }

TableContent
 = "effect" _ name:Name _? ";" _?                                         { return { type: 'effect', name: name }; }
 / "effect" _? "[" _? "]" _? name:Name _? ";" _?                          { return { type: 'effect-array', name: name }; } 

TableItem
 = "item" _ table:Name _ id:Name _? "{" _? "}" _?                                 { return { type: 'item', table: table, id: id, content: []  }; }
 / "item" _ table:Name _ id:Name _? "{" _? content:TableItemContent* _? "}" _?    { return { type: 'item', table: table, id: id, content: content }; }

TableItemContent
 = name:Name _? "=" _? value:TableItemValue _? ";" _?                             { return { type: 'item-value', name: name, value: value }; }
 / name:Name _? "=" _? value:TableItemArray _? ";" _?                             { return { type: 'item-value', name: name, value: value }; }

TableItemValue
 = ConstantEffect
 / Constant

TableItemArray
 = "[" _? "]"									                   { return []; }
 / "[" _? values:TableItemArrayValues _? "]"                       { return values; }
 
TableItemArrayValues
 = begin:TableItemArrayValue _? "," _? end:TableItemArrayValues    { return [begin].concat(end); }
 / value:TableItemArrayValue                                       { return [value]; }

TableItemArrayValue
 = TableItemValue
 / TableItemArray

ConstantEffect
 = need:Name _? "(" _? level:ConstantNumber _? ")"                 { return { type: 'constant-effect', need: need, level: level }; }


Step
 = "step" _ name:Name _? "{" _? content:StepContent* _? "}" _?                                          { return { name: name, parameters: [], content: content }; }
 / "step" _ name:Name _? "(" _? parameters:Parameters? _? ")" _? "{" _? content:StepContent*  "}" _?    { return { name: name, parameters: parameters, content: content }; }

StepContent
 = Precondition
 / Postcondition
 / Action
 / SubStep
 / StepEffect

StepEffect
 = "effect" _ value:ConstantEffect _? ";" _?                                          { return { type: 'effect', value: value }; }
 / "effect" _ value:Reference _? ";" _?                                               { return { type: 'effect', value: value }; }

Reference
 = name:Names                                                                         { return { type: 'reference', name: name } }

SubStep
 = "step" _ name:Name _? "(" _? parameters:CallParameters _? ")" _? ";" _?            { return { type: 'step', name: name, parameters:parameters }; }

Action
 = "action" _ name:Name _? ( "(" _? ")" )? ";" _?                                     { return { type: 'action', name: name, parameters: [] }; }
 / "action" _ name:Name _? "(" _? parameters:CallParameters _? ")" _? ";" _?          { return { type: 'action', name: name, parameters: parameters }; }

Postcondition
 = "postcondition" _ name:Name _? "(" _? parameters:CallParameters _? ")" _? ";" _?   { return { type: 'postcondition', name: name, parameters:parameters }; }

Precondition
 = "precondition" _ name:Name _? "(" _? parameters:CallParameters _? ")" _? ";" _?    { return { type: 'precondition', name: name, parameters:parameters }; }

CallParameters
 = begin:CallParameter _? "," _? end:CallParameters { return [begin].concat(end) }
 / cp:CallParameter { return [cp]; }

CallParameter
 = Names 
 / Constant


Constant
 = ConstantNumber

ConstantNumber
 = digits:[0-9]+ { return { type: 'constant-number', value: digits.join('') }; }

Parameters
 = begin:Parameter _? "," _? end:Parameters { return [begin].concat(end) }
 / p:Parameter { return [p]; }

Parameter
  = type:Name _ name:Name { return { type: type, name: name } }

Names
 = begin:Name _? "." _? end:Names { return [begin].concat(end).join('.'); }
 / n:Name { return n; }

Name
 = begin:[a-zA-z_] end:[a-zA-Z0-9_]*            { return begin + end.join(''); }

WhiteSpace
 = ' '
 / '\n'
 / '\r'
 / '\t'
_
 = WhiteSpace+ { return null; }