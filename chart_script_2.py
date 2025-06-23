import plotly.express as px
import pandas as pd
import json

# Data for the Stock Portfolio Manager features
data = {
    "features": [
        {"name": "Add Investment", "category": "Portfolio Mgmt"},
        {"name": "Remove Invest", "category": "Portfolio Mgmt"},
        {"name": "Update Price", "category": "Portfolio Mgmt"},
        {"name": "View Portfolio", "category": "View & Analysis"},
        {"name": "View Summary", "category": "View & Analysis"},
        {"name": "Detail Report", "category": "View & Analysis"},
        {"name": "Top Performers", "category": "View & Analysis"},
        {"name": "Losing Invest", "category": "View & Analysis"},
        {"name": "Sort by Value", "category": "Data Ops"},
        {"name": "Sort by Symbol", "category": "Data Ops"},
        {"name": "Save Portfolio", "category": "File Ops"},
        {"name": "Load Portfolio", "category": "File Ops"},
        {"name": "Export to CSV", "category": "File Ops"},
        {"name": "Real-time Upd", "category": "Simulation"},
        {"name": "Sample Data", "category": "Simulation"}
    ]
}

# Create dataframe
df = pd.DataFrame(data["features"])

# Add a parent column for the sunburst chart
df_sunburst = df.copy()
df_sunburst['parent'] = ''
df_sunburst['id'] = df_sunburst['name']
df_sunburst['values'] = 1

# Add category rows
categories = df['category'].unique()
category_data = []
for cat in categories:
    category_data.append({
        'name': cat,
        'category': '',
        'parent': '',
        'id': cat,
        'values': len(df[df['category'] == cat])
    })

# Combine data
df_categories = pd.DataFrame(category_data)
df_combined = pd.concat([df_categories, df_sunburst], ignore_index=True)

# Update parent for features
df_combined.loc[df_combined['category'] != '', 'parent'] = df_combined.loc[df_combined['category'] != '', 'category']

# Create sunburst chart
fig = px.sunburst(
    df_combined,
    names='name',
    parents='parent',
    values='values',
    title='Stock Portfolio Manager Features',
    color_discrete_sequence=['#1FB8CD', '#FFC185', '#ECEBD5', '#5D878F', '#D2BA4C']
)

# Update layout
fig.update_layout(
    uniformtext_minsize=12,
    uniformtext_mode='hide'
)

# Update traces for better text display
fig.update_traces(
    textinfo="label",
    hovertemplate='<b>%{label}</b><extra></extra>'
)

# Save the chart
fig.write_image('portfolio_manager_features.png')