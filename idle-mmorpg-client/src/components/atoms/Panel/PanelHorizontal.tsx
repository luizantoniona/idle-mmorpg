import "./Panel.css";
import React from "react";
import { Panel } from "./Panel";

interface PanelHorizontalProps extends React.HTMLAttributes<HTMLDivElement> {
    children: React.ReactNode;
    className?: string;
}

export const PanelHorizontal: React.FC<PanelHorizontalProps> = ({
    children,
    className = "",
    ...props
}) => {
    return (
        <Panel className={`panel-horizontal ${className}`} {...props}>
            {children}
        </Panel>
    );
};
