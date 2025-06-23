import plotly.graph_objects as go
import plotly.express as px
import json

# Data from the provided JSON
data = {
    "files": {
        "headers": [
            {"name": "Stock.h", "size": 1113},
            {"name": "Investment.h", "size": 1250},
            {"name": "Portfolio.h", "size": 2572}
        ],
        "implementation": [
            {"name": "Stock.cpp", "size": 2890},
            {"name": "Investment.cpp", "size": 4545},
            {"name": "Portfolio.cpp", "size": 14634},
            {"name": "main.cpp", "size": 10694}
        ],
        "project": [
            {"name": "Makefile", "size": 1075},
            {"name": "README.md", "size": 6497}
        ]
    }
}

# Prepare data for plotting
files = []
sizes = []
types = []
colors = []

# Color mapping using the specified brand colors in order
color_map = {
    "Headers": "#1FB8CD",        # Strong cyan
    "Implementation": "#FFC185",  # Light orange  
    "Project": "#ECEBD5"         # Light green
}

# Process each file type
for file_type, file_list in data["files"].items():
    type_name = file_type.capitalize()
    for file_info in file_list:
        files.append(file_info["name"])
        # Convert bytes to KB for better readability
        size_kb = round(file_info["size"] / 1000, 1)
        sizes.append(size_kb)
        types.append(type_name)
        colors.append(color_map[type_name])

# Create horizontal bar chart
fig = go.Figure()

# Add bars for each file type
for file_type in ["Headers", "Implementation", "Project"]:
    type_files = [f for i, f in enumerate(files) if types[i] == file_type]
    type_sizes = [s for i, s in enumerate(sizes) if types[i] == file_type]
    
    fig.add_trace(go.Bar(
        y=type_files,
        x=type_sizes,
        name=file_type,
        orientation='h',
        marker_color=color_map[file_type],
        hovertemplate='<b>%{y}</b><br>Size: %{x}k bytes<extra></extra>'
    ))

# Update layout
fig.update_layout(
    title="C++ Portfolio Manager File Structure",
    xaxis_title="Size (KB)",
    yaxis_title="Files",
    barmode='group',
    legend=dict(
        orientation='h', 
        yanchor='bottom', 
        y=1.05, 
        xanchor='center', 
        x=0.5
    )
)

# Save the chart
fig.write_image("cpp_portfolio_structure.png")