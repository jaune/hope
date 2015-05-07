var $ = require('jquery'),
	cytoscape = require('cytoscape');

$(function(){ // on dom ready



function stepsToElements (steps) {
	var nodes = [];
	var edges = [];

	var preconditions  = {};
	var postconditions  = {};
	var stepIds = {};

	steps.forEach(function (step, index) {
		var stepId = 'node-'+index;
		
		nodes.push({
			data: {
				id: stepId,
				label: step.name
			},
			classes: 'step'
		});

		step.preconditions.forEach(function (precondition, index) {
			var preconditionId = stepId+'-pre-'+index;
			nodes.push({
				data: {
					id: preconditionId,
					parent: stepId,
					label: precondition.name
				},
				classes: 'precondition'
			});

			if (!preconditions[precondition.name]) {
				preconditions[precondition.name] = [{ id: preconditionId }];
			} else {
				preconditions[precondition.name].push({ id: preconditionId });
			}
			
		});

		step.postconditions.forEach(function (postcondition, index) {
			var postconditionId = stepId+'-post-'+index;
			nodes.push({
				data: {
					id: postconditionId,
					parent: stepId,
					label: postcondition.name
				},
				classes: 'postcondition'
			});

			if (!postconditions[postcondition.name]) {
				postconditions[postcondition.name] = [{ id: postconditionId }];
			} else {
				postconditions[postcondition.name].push({ id: postconditionId });
			}
		});

		stepIds[step.name] = stepId;
	});

	steps.forEach(function (step, index) {
		if (!step.steps) {
			return;
		}
		step.steps.forEach(function (child, index) {
			edges.push({
				data: {
					id: stepIds[step.name]+'-->'+stepIds[child.name],
					source: stepIds[step.name],
					target: stepIds[child.name]
				}
			});
		});
	});

	Object.keys(preconditions).forEach(function (postName) {
		if (!postconditions[postName]) {
			return;
		}

		preconditions[postName].forEach(function (precondition) {
			postconditions[postName].forEach(function (postcondition) {
		
				edges.push({
					data: {
						id: postcondition.id+'-->'+precondition.id,
						source: postcondition.id,
						target: precondition.id
					}
				});

			});
		});

		
	});

	return { nodes: nodes, edges: edges};
}

var steps = [
	{
		name: 'GoTo',
		preconditions: [],
		postconditions: [
			{ name: 'At' }
		],
		action: {
			name: 'GoTo'
		}
	},
	{
		name: 'GoToAdjacent',
		preconditions: [],
		postconditions: [
			{ name: 'AdjacentTo' }
		],
		steps: [
			{ name: 'GoTo' }
		]
	},
	{
		name: 'TakeItem',
		preconditions: [
			{ name: 'AdjacentTo' },
			{ name: 'HasItemQuantityAt' }
		],
		postconditions: [
			{ name: 'HasItemQuantity' }
		]
	},
	{
		name: 'DropItem',
		preconditions: [
			{ name: 'AdjacentTo' },
			{ name: 'HasItemQuantity' }
		],
		postconditions: [
			{ name: 'HasItemQuantityAt' }
		]
	},
	{
		name: 'Construct',
		preconditions: [
			{ name: 'AdjacentTo' },
			{ name: 'HasItemQuantityAt' }
		],
		postconditions: [
		],
		action: {
			name: 'Construct'
		}
	}
];


/*
var elements = {
	nodes: [
      { data: { id: 'a', parent: 'b' } },
      { data: { id: 'b' } },
      { data: { id: 'c', parent: 'b' } },
      { data: { id: 'd' } },
      { data: { id: 'e' } },
      { data: { id: 'f', parent: 'e' } },
      { data: { id: 'g', parent: 'f' } }
    ],
    edges: [
      { data: { id: 'ad', source: 'a', target: 'd' } },
      { data: { id: 'eb', source: 'e', target: 'b' } }
]};
*/

var elements = stepsToElements(steps);


var cy = cytoscape({
  container: document.getElementById('cy'),
  
  style: [
    {
      selector: 'node',
      css: {
        'content': 'data(label)',
        'text-valign': 'center',
        'text-halign': 'center'
      }
    },
    {
      selector: '$node > node',
      css: {
        'padding-top': '20px',
        'padding-left': '20px',
        'padding-bottom': '20px',
        'padding-right': '20px',
        'text-valign': 'top',
        'text-halign': 'center'
      }
    },
    {
      selector: 'edge',
      css: {
      	'content': 'data(label)',
        'target-arrow-shape': 'triangle'
      }
    },
    {
      selector: ':selected',
      css: {
        'background-color': 'black',
        'line-color': 'black',
        'target-arrow-color': 'black',
        'source-arrow-color': 'black'
      }
    },

    {
      selector: '.precondition',
      css: {
        'background-color': '#00ff00',
        'line-color': '#ff00ff',
        'target-arrow-color': '#ff00ff',
        'source-arrow-color': '#ff00ff'
      }
    },

    {
      selector: '.postcondition',
      css: {
        'background-color': '#ff0000',
        'line-color': '#ff00ff',
        'target-arrow-color': '#ff00ff',
        'source-arrow-color': '#ff00ff'
      }
    }

    
  ],
  
  elements: elements,
  
  layout: {
    name: 'cose',
    padding: 5
  }
});

});